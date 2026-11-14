#ifndef QUNITCONVERTOR_H
#define QUNITCONVERTOR_H

#include <map>
#include <math.h>
#include <stdexcept>
#include <vector>

#include "qlinearfunction.h"
#include "qunitconversionrule.h"
#include "qaliasdictionary.h"

/**
 * @brief The QUnitConvertor class provides tool for converting units stored
 * in a string form. It uses "base" unit for each "family" (length, speed etc)
 * and perform conversions inside a family through conversion to and from base unit.
 */
template<class String>
class QUnitConvertor
{
public:
    /**
     * @brief Default constructor
     */
    QUnitConvertor() = default;

    /**
     * @brief Checks if unit conversion from in unit to out unit is possible
     * @param in unit to convert from
     * @param out unit to convert to
     * @return true if conversion is possible, false otherwise
     */
    bool canConvert(const String & in, const String & out) const
    {
        return convert(in, out).isValid();
    }

    /**
     * @brief Converts from in unit to out unit
     * @param in unit to convert from
     * @param out unit to convert to
     * @return QLinearFunction object containing conversion from in to out unit
     */
    QLinearFunction convert(const String & in, const String & out) const
    {
        String actualIn  = m_aliases.contains(in)  ? m_aliases.name(in)  : in;
        String actualOut = m_aliases.contains(out) ? m_aliases.name(out) : out;
        if (actualIn == actualOut)
            return {1, 0};
        auto itIn  = m_familiesByUnit.find(actualIn);
        auto itOut = m_familiesByUnit.find(actualOut);
        if (itIn == m_familiesByUnit.end() || itOut == m_familiesByUnit.end())
            return {};
        if (itIn->second != itOut->second)
            return {};
        return QLinearFunction::combined(fromBase(actualIn).inverted(), fromBase(actualOut));
    }

    /**
     * @brief Converts a given value from in unit to out unit
     * @param value to convert
     * @param in unit to convert from
     * @param out unit to convert to
     * @param defaultValue value to return if conversion fails
     * @return value converted to out unit
     * @details Supports aliases for unit names, see QAliasDictionary
     */
    double convert(double value, const String & in, const String & out, double defaultValue = NAN) const
    {
        QLinearFunction function = convert(in, out);
        if (!function.isValid())
            return defaultValue;
        return function.y(value);
    }

    /**
     * @brief Adds a conversion rule to convertor
     * @param rule rule to add
     * @details This function doesn't convert an alias for a unit to an actual unit name, so make sure to
     * pass here an actual unit name
     * @throw std::invalid_argument if the rule's family has a different base unit, or its unit
     * or base unit belongs to another family
     */
    void addConversionRule(const QUnitConversionRule<String> & rule)
    {
        auto itFamily = m_baseUnitsByFamilies.find(rule.family());
        if (itFamily != m_baseUnitsByFamilies.end() && itFamily->second != rule.baseUnit())
            throw std::invalid_argument("Incorrect rule added: incorrect family base unit");
        auto itBaseUnit = m_familiesByUnit.find(rule.baseUnit());
        if (itBaseUnit != m_familiesByUnit.end() && itBaseUnit->second != rule.family())
            throw std::invalid_argument("Incorrect rule added: incorrect base unit family");
        auto itUnit = m_familiesByUnit.find(rule.unit());
        if (itUnit != m_familiesByUnit.end() && itUnit->second != rule.family())
            throw std::invalid_argument("Incorrect rule added: incorrect unit family");
        // TODO: reject a rule with base -> base conversion
        m_baseUnitsByFamilies[rule.family()] = rule.baseUnit();
        m_familiesByUnit[rule.baseUnit()] = rule.family();
        m_familiesByUnit[rule.unit()] = rule.family();
        m_baseToUnit.insert_or_assign(rule.unit(), rule.convertFunction());
    }

    /**
     * @brief Clears unit convertor removing all unit conversion rules
     */
    void clear()
    {
        m_familiesByUnit.clear();
        m_baseUnitsByFamilies.clear();
        m_baseToUnit.clear();
    }

    /**
     * @brief Method provides access to a list of families of units in this convertor
     * @return vector containing a list of unit families
     */
    std::vector<String> families() const
    {
        std::vector<String> result;
        result.reserve(m_baseUnitsByFamilies.size());
        for (const auto & [name, _] : m_baseUnitsByFamilies)
            result.push_back(name);
        return result;
    }

    /**
     * @brief Gets a family for a given unit
     * @param unit unit to return a family
     * @return a family name or an empty string if unit is unknown to convertor
     */
    String family(const String & unit) const
    {
        String actualUnit = m_aliases.contains(unit) ? m_aliases.name(unit) : unit;
        auto it = m_familiesByUnit.find(actualUnit);
        if (it == m_familiesByUnit.end())
            return {};
        return it->second;
    }

    /**
     * @brief Gets a list of units with a possible connection to/from a given unit
     * @param unit unit to get a list of conversions
     * @return vector with units with possible conversion to a given unit, including a given unit.
     * If conversion to/from a given unit is unknown returns an empty vector
     */
    std::vector<String> conversions(const String & unit) const
    {
        return units(family(unit));
    }

    /**
     * @brief Method provides access to a list of units in this convertor within a given
     * family, effectively providing a list of units with a possible conversion from
     * any unit of this list to any other
     * @param family family to return unit list
     * @return vector containing a list of units known by this unit convertor within the family
     */
    std::vector<String> units(const String & family) const
    {
        std::vector<String> result;
        for (const auto & [unit, unitFamily] : m_familiesByUnit)
            if (unitFamily == family)
                result.push_back(unit);
        return result;
    }

    /**
     * @brief Sets aliases from a QAliasDictionary object
     */
    void setAliases(QAliasDictionary<String> aliases)
    {
        m_aliases = std::move(aliases);
    }

    /**
     * @brief Adds one alias
     */
    void addAlias(String name, String alias)
    {
        m_aliases.addAlias(std::move(name), std::move(alias));
    }

    /**
     * @brief Removes all alias rules
     */
    void clearAliases()
    {
        m_aliases.clear();
    }

    /**
     * @brief Gets unit name by alias using internal alias dictionary
     * @param alias unit alias to get unit name
     * @return unit name or an empty string if a specified alias is not found
     */
    String unitName(const String & alias) const
    {
        return m_aliases.name(alias);
    }

    /**
     * @brief Gets the base unit for a given family
     * @param family family name
     * @return base unit name or an empty string if the family is unknown
     */
    String baseUnit(const String & family) const
    {
        auto it = m_baseUnitsByFamilies.find(family);
        if (it == m_baseUnitsByFamilies.end())
            return {};
        return it->second;
    }

protected:
    /**
     * @brief Gets a conversion from the family base unit to a given unit
     * @param unit actual unit name known to the convertor
     * @return conversion function, identity for a base unit
     */
    QLinearFunction fromBase(const String & unit) const
    {
        auto it = m_baseToUnit.find(unit);
        if (it == m_baseToUnit.end())
            return {1, 0};
        return it->second;
    }

    std::map<String, String> m_familiesByUnit;          ///< Key is a unit, Value is a corresponding family. Base units are also put here
    std::map<String, String> m_baseUnitsByFamilies;     ///< Key is a family name, Value is a corresponding base unit
    std::map<String, QLinearFunction> m_baseToUnit;     ///< Key is a non-base unit, Value is a conversion from its family base unit to it
    QAliasDictionary<String> m_aliases;
};

#endif // QUNITCONVERTOR_H
