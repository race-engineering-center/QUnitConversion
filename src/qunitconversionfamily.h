#ifndef QUNITCONVERSIONFAMILY_H
#define QUNITCONVERSIONFAMILY_H

#include <QMap>
#include <cmath>

#include "qunitconversionrule.h"

/**
 * @brief The QUnitConversionFamily class is an internal class that provides
 * a conversion by holding all of the conversion rules for a single family
 */
class QUnitConversionFamily
{
public:
    QUnitConversionFamily();
    QUnitConversionFamily(const QString & familyName, const QString & baseUnit);

    /**
     * @brief Adds a conversion rule to convertor
     * @param rule rule to add
     * @details
     */
    void addConversionRule(const QUnitConversionRule & rule);

    /**
     * @brief Converts from in unit to out unit
     * @param in unit to convert from
     * @param out unit to convert to
     * @return QLinearFunction object containing conversion from in to out unit
     */
    QLinearFunction convert(const QString & in, const QString & out) const;

    /**
     * @brief Converts a given value from in unit to out unit
     * @param value to convert
     * @param in unit to convert from
     * @param out unit to convert to
     * @return value converted to
     */
    double convert(double value, const QString & in, const QString & out) const;

protected:
    QMap <QString, QUnitConversionRule> m_rules;    ///< Key is a unit, it's assumed that all rules have the same base unit
    QString m_baseUnit;     ///< Base unit for this family
    QString m_family;       ///< Family name
};

#endif // QUNITCONVERSIONFAMILY_H
