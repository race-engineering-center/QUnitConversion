#include "qunitconversionfamily.h"

QUnitConversionFamily::QUnitConversionFamily()
{

}

QUnitConversionFamily::QUnitConversionFamily(const QString &familyName, const QString &baseUnit)
{
    m_family = familyName;
    m_baseUnit = baseUnit;
}

void QUnitConversionFamily::addConversionRule(const QUnitConversionRule &rule)
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
    m_rules.insert(rule.unit(), rule);
}

QLinearFunction QUnitConversionFamily::convert(const QString &in, const QString &out) const
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

double QUnitConversionFamily::convert(double value, const QString &in, const QString &out) const
{
    QLinearFunction function = convert(in, out);
    if (function.isValid())
        return function.y(value);
    return NAN;
}
