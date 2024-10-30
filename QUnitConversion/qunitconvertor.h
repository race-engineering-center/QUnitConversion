#ifndef QUNITCONVERTOR_H
#define QUNITCONVERTOR_H

#include <QMap>

#include <math.h>

#include "qlinearfunction.h"
#include "qunitconversionfamily.h"
#include "qaliasdictionary.h"

/**
 * @brief The QUnitConvertor class provides tool for converting units stored
 * in a string form. It uses "base" unit for each "family" (length, speed etc)
 * and perform conversions inside a family through conversion to and from base unit.
 */
template<typename String>
class QUnitConvertor
{
    friend class QUnitConvertorTests;
public:
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
        if (in == out)
            return {1, 0};
        String actualIn, actualOut;
        if (m_aliases.contains(in))
            actualIn = m_aliases.name(in);
        else
            actualIn = in;
        if (m_aliases.contains(out))
            actualOut = m_aliases.name(out);
        else
            actualOut = out;
        auto inFamilyIt = m_familiesByUnit.find(actualIn);

        String outFamily = m_familiesByUnit.value(actualOut);
        if (inFamilyIt == m_familiesByUnit.end() || inFamilyIt.value() != outFamily)
            return {};

        return m_families[inFamilyIt.value()].convert(actualIn, actualOut);
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
     * @details This function doesn't convert an alas for a unit to an actual unit name, so make sure to
     * pass here an actual unit name
     * @throw std::invalid_argument if a passed rule has existing family with different base unit,
     * existing unit with different family or existing unit with a different family or base unit
     */
    void addConversionRule(const QUnitConversionRule<String> & rule)
    {
        if (m_baseUnitsByFamilies.contains(rule.family()) && m_baseUnitsByFamilies[rule.family()] != rule.baseUnit())
            throw std::invalid_argument("Incorrect rule added: incorrect family base unit");
        if (m_familiesByUnit.contains(rule.baseUnit()) && m_familiesByUnit[rule.baseUnit()] != rule.family())
            throw std::invalid_argument("Incorrect rule added: incorrect base unit family");
        if (m_familiesByUnit.contains(rule.unit()) && m_familiesByUnit[rule.unit()] != rule.family())
            throw std::invalid_argument("Incorrect rule added: incorrect unit family");
        if (!m_families.contains(rule.family()))
        {
            QUnitConversionFamily<String> family;
            family.addConversionRule(rule);
            m_families.insert(rule.family(), family);
            m_baseUnitsByFamilies.insert(rule.family(), rule.baseUnit());
            m_familiesByUnit.insert(rule.baseUnit(), rule.family());
        }
        else
        {
            m_families[rule.family()].addConversionRule(rule);
        }
        m_familiesByUnit.insert(rule.unit(), rule.family());
    }

    /**
     * @brief Clears unit convertor removing all unit conversion rules
     */
    void clear()
    {
        m_families.clear();
        m_familiesByUnit.clear();
        m_baseUnitsByFamilies.clear();
    }

    /**
     * @brief Method provides access to a list of families of units in this convertor
     * @return StringList containing a list of unit families
     */
    std::vector<String> families() const
    {
        std::vector<String> result;
        result.reserve(m_families.size());
        for (auto it = m_families.begin(); it != m_families.end(); ++it)
            result.push_back(it.key());

        return result;
    }

    /**
     * @brief Gets a family for a given unit
     * @param unit unit to return a family
     * @return a family name or an empty string if unit is unknown to convertor
     */
    String family(const String & unit) const
    {
        String actualUnit;
        if (m_aliases.contains(unit))
            actualUnit = m_aliases.name(unit);
        else
            actualUnit = unit;
        return m_familiesByUnit.value(actualUnit);
    }

    /**
     * @brief Gets a list of units with a possible connection to/from a given unit
     * @param unit unit to get a list of conversions
     * @return StringList with units with possible conversion to a given unit, including a given unit. If
     * conversion to/from a given unit is unknown returns an empty list
     */
    std::vector<String> conversions(const String & unit) const
    {
        return units(family(unit));
    }

    /**
     * @brief Method provides access to a list of units in this convertor within a given
     * family, effectively providing a list of unit with a possible conversion from
     * any unit of this list to any other
     * @param family family to return unit list
     * @return StringList containing a list of units known by this unit convertor
     */
    std::vector<String> units(const String &family) const
    {
        std::vector<String> result;
        result.reserve(m_familiesByUnit.size());
        for (auto it = m_familiesByUnit.begin(); it != m_familiesByUnit.end(); ++it)
            if (it.value() == family)
                result.push_back(it.key());

        return result;
    }

    /**
     * @brief adds aliases from the object QAliasDictionary
     */
    void setAliases(QAliasDictionary<String> aliases)
    {
        m_aliases = std::move(aliases);
    }

    /**
     * @brief adds one alias
     */
    void addAlias(String name, String alias)
    {
        m_aliases.addAlias(name, alias);
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

protected:
    QMap<String, String> m_familiesByUnit;   ///< Key is a unit, Value is a corresponding family. Base units are also put here
    QMap<String, String> m_baseUnitsByFamilies;  ///< Key is a family name, Value is a corresponding base unit
    QMap<String, QUnitConversionFamily<String>> m_families;   ///< Key is a family name, Value is a family
    QAliasDictionary<String> m_aliases;
};

#endif // QUNITCONVERTOR_H
