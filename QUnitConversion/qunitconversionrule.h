#ifndef QUNITCONVERSIONRULE_H
#define QUNITCONVERSIONRULE_H

#include <QString>

#include "qlinearfunction.h"

/**
 * @brief The QUnitConversionRule class represents a unit conversion rule from
 * base unit to second unit within the specified family. Note that in QUnitConvertor
 * class each family can be represented with the single base unit. In other words you
 * can't have two unit conversion rules with the same family but different base units
 */
class QUnitConversionRule
{
public:
    QUnitConversionRule() = default;

    QUnitConversionRule(const QString & family,
                        const QString & baseUnit,
                        const QString & unit,
                        const QLinearFunction & convertFunction);

    QUnitConversionRule(const QString & family,
                        const QString & baseUnit,
                        const QString & unit,
                        double k, double b);

    QString family() const;
    void setFamily(const QString &family);

    QString baseUnit() const;
    void setBaseUnit(const QString &baseUnit);

    QString unit() const;
    void setUnit(const QString &unit);

    QLinearFunction convertFunction() const;
    void setConvertFunction(const QLinearFunction &function);

protected:
    QString m_family;   ///< Family name for this pair of units, like length, speed
    QString m_baseUnit; ///< Base unit for this family
    QString m_unit;     ///< Unit to convert to
    QLinearFunction m_convertFunction;  ///< Linear function to perform conversion from base unit to unit
};

#endif // QUNITCONVERSIONRULE_H
