#include "qunitconversionrule.h"

QUnitConversionRule::QUnitConversionRule()
{

}

QString QUnitConversionRule::family() const
{
    return m_family;
}

void QUnitConversionRule::setFamily(const QString &family)
{
    m_family = family;
}

QString QUnitConversionRule::baseUnit() const
{
    return m_baseUnit;
}

void QUnitConversionRule::setBaseUnit(const QString &baseUnit)
{
    m_baseUnit = baseUnit;
}

QString QUnitConversionRule::unit() const
{
    return m_unit;
}

void QUnitConversionRule::setUnit(const QString &unit)
{
    m_unit = unit;
}

QLinearFunction QUnitConversionRule::convertFunction() const
{
    return m_convertFunction;
}

void QUnitConversionRule::setConvertFunction(const QLinearFunction &function)
{
    m_convertFunction = function;
}
