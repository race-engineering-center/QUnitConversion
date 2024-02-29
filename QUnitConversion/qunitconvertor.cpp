#include "qunitconvertor.h"

bool QUnitConvertor::canConvert(const QString &in, const QString &out) const
{
    return convert(in, out).isValid();
}

QLinearFunction QUnitConvertor::convert(const QString &in, const QString &out) const
{
    if (in == out)
        return {1, 0};
    QString actualIn, actualOut;
    if (m_aliases.contains(in))
        actualIn = m_aliases.name(in);
    else
        actualIn = in;
    if (m_aliases.contains(out))
        actualOut = m_aliases.name(out);
    else
        actualOut = out;
    QString inFamily = m_familiesByUnit.value(actualIn);
    QString outFamily = m_familiesByUnit.value(actualOut);
    if (inFamily.isEmpty() || inFamily != outFamily)
        return {};
    return m_families[inFamily].convert(actualIn, actualOut);
}

double QUnitConvertor::convert(double value, const QString &in, const QString &out, double defaultValue) const
{
    QLinearFunction function = convert(in, out);
    if (!function.isValid())
        return defaultValue;
    return function.y(value);
}

void QUnitConvertor::loadFromJson(const QJsonObject &json)
{
    QJsonArray rules = json["rules"].toArray();
    for (const auto & r: std::as_const(rules))
    {
        QJsonObject rule = r.toObject();
        QString baseUnit = rule["base"].toString();
        QString familyName = rule["family"].toString();
        QJsonArray conversions = rule["conversions"].toArray();
        for (const auto & c: std::as_const(conversions))
        {
            QJsonObject conversion = c.toObject();
            QString unit = conversion["unit"].toString();
            double k = conversion["k"].toDouble();
            double b = conversion["b"].toDouble();
            if (unit.isEmpty() || qFuzzyIsNull(k))
                continue;
            addConversionRule(QUnitConversionRule(familyName,
                                                  baseUnit,
                                                  unit,
                                                  k,
                                                  b
                                                  ));
        }
    }
}

QJsonObject QUnitConvertor::toJson() const
{
    // TODO implement
    Q_ASSERT_X(false, Q_FUNC_INFO, "Save to JSON is not yet implemented");
    return {};
}

void QUnitConvertor::addConversionRule(const QUnitConversionRule &rule)
{
    if (m_baseUnitsByFamilies.contains(rule.family()) && m_baseUnitsByFamilies[rule.family()] != rule.baseUnit())
        throw std::invalid_argument("Incorrect rule added: incorrect family base unit");
    if (m_familiesByUnit.contains(rule.baseUnit()) && m_familiesByUnit[rule.baseUnit()] != rule.family())
        throw std::invalid_argument("Incorrect rule added: incorrect base unit family");
    if (m_familiesByUnit.contains(rule.unit()) && m_familiesByUnit[rule.unit()] != rule.family())
        throw std::invalid_argument("Incorrect rule added: incorrect unit family");
    if (!m_families.contains(rule.family()))
    {
        QUnitConversionFamily family;
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

void QUnitConvertor::clear()
{
    m_families.clear();
    m_familiesByUnit.clear();
    m_baseUnitsByFamilies.clear();
}

QStringList QUnitConvertor::families() const
{
    return m_families.keys();
}

QString QUnitConvertor::family(const QString &unit) const
{
    QString actualUnit;
    if (m_aliases.contains(unit))
        actualUnit = m_aliases.name(unit);
    else
        actualUnit = unit;
    return m_familiesByUnit.value(actualUnit);
}

QStringList QUnitConvertor::conversions(const QString &unit) const
{
    return units(family(unit));
}

QStringList QUnitConvertor::units(const QString &family) const
{
    return m_familiesByUnit.keys(family);
}

void QUnitConvertor::clearAliases()
{
    m_aliases.clear();
}

QString QUnitConvertor::unitName(const QString &alias) const
{
    return m_aliases.name(alias);
}
