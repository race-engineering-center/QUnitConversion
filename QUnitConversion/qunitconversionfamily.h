#ifndef QUNITCONVERSIONFAMILY_H
#define QUNITCONVERSIONFAMILY_H

#include <QMap>

#include <cmath>
#include <stdexcept>

#include "qunitconversionrule.h"

/**
 * @brief The QUnitConversionFamily class is an internal class that provides
 * a conversion by holding all of the conversion rules for a single family
 */
template<typename String>
class QUnitConversionFamily
{
public:
    QUnitConversionFamily() = default;
    QUnitConversionFamily(String familyName, String baseUnit)
        : m_family(std::move(familyName)),
        m_baseUnit(std::move(baseUnit))
    {
    }

    /**
     * @brief Adds a conversion rule to convertor
     * @param rule rule to add
     * @details
     */
    void addConversionRule(QUnitConversionRule<String> rule)
    {
        if (m_rules.isEmpty())
        {
            m_family = rule.family();
            m_baseUnit = rule.baseUnit();
        }
        else
        {
            if (m_family != rule.family() || m_baseUnit != rule.baseUnit())
                throw std::invalid_argument("Incorrect rule added to family");      // Don Corleone will be unhappy
        }
        auto unit = rule.unit();
        m_rules.insert(std::move(unit), std::move(rule));
    }

    /**
     * @brief Converts from in unit to out unit
     * @param in unit to convert from
     * @param out unit to convert to
     * @return QLinearFunction object containing conversion from in to out unit
     */
    QLinearFunction convert(const String & in, const String & out) const
    {
        if (m_rules.isEmpty())
            return {};

        if (in == m_baseUnit && m_rules.contains(out))  // conversion from base unit to unit
            return m_rules[out].convertFunction();
        if (m_rules.contains(in) && out == m_baseUnit)  // converson from unit to base unit
            return m_rules[in].convertFunction().inversed();

        // conversion from one unit to another through the base unit if possible
        QLinearFunction inToBase = m_rules[in].convertFunction().inversed();
        QLinearFunction baseToOut = m_rules[out].convertFunction();
        if (!inToBase.isValid() || !baseToOut.isValid())    // one of the conversions is not present
            return {};
        return QLinearFunction::combined(inToBase, baseToOut);
    }

    /**
     * @brief Converts a given value from in unit to out unit
     * @param value to convert
     * @param in unit to convert from
     * @param out unit to convert to
     * @return value converted to
     */
    double convert(double value, const String & in, const String & out) const
    {
        QLinearFunction function = convert(in, out);
        if (function.isValid())
            return function.y(value);
        return NAN;
    }

protected:
    QMap<String, QUnitConversionRule<String>> m_rules;    ///< Key is a unit, it's assumed that all rules have the same base unit
    String m_baseUnit;     ///< Base unit for this family
    String m_family;       ///< Family name
};

#endif // QUNITCONVERSIONFAMILY_H
