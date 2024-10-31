#ifndef QUNITCONVERSIONRULE_H
#define QUNITCONVERSIONRULE_H

#include <utility>

#include "qlinearfunction.h"

/**
 * @brief The QUnitConversionRule class represents a unit conversion rule from
 * base unit to second unit within the specified family. Note that in QUnitConvertor
 * class each family can be represented with the single base unit. In other words you
 * can't have two unit conversion rules with the same family but different base units
 */
template<typename String>
class QUnitConversionRule
{
public:
    QUnitConversionRule() = default;

    QUnitConversionRule(String family,
                        String baseUnit,
                        String unit,
                        QLinearFunction convertFunction)
        : m_family(std::move(family)),
        m_baseUnit(std::move(baseUnit)),
        m_unit(std::move(unit)),
        m_convertFunction(std::move(convertFunction))
    {
    }

    QUnitConversionRule(String family,
                        String baseUnit,
                        String unit,
                        double k, double b)
        : m_family(std::move(family)),
        m_baseUnit(std::move(baseUnit)),
        m_unit(std::move(unit)),
        m_convertFunction(k, b)
    {
    }


    String family() const
    {
        return m_family;
    }

    void setFamily(const String &family)
    {
        m_family = family;
    }

    String baseUnit() const
    {
        return m_baseUnit;
    }

    void setBaseUnit(const String &baseUnit)
    {
        m_baseUnit = baseUnit;
    }

    String unit() const
    {
        return m_unit;
    }

    void setUnit(const String &unit)
    {
        m_unit = unit;
    }

    QLinearFunction convertFunction() const
    {
        return m_convertFunction;
    }

    void setConvertFunction(const QLinearFunction &function)
    {
        m_convertFunction = function;
    }

protected:
    String m_family;   ///< Family name for this pair of units, like length, speed
    String m_baseUnit; ///< Base unit for this family
    String m_unit;     ///< Unit to convert to
    QLinearFunction m_convertFunction;  ///< Linear function to perform conversion from base unit to unit
};

#endif // QUNITCONVERSIONRULE_H
