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
class QUnitConvertor
{
    friend class QUnitConvertorTests;
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
    bool canConvert(const QString & in, const QString & out) const;

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
     * @param defaultValue value to return if conversion fails
     * @return value converted to out unit
     * @details Supports aliases for unit names, see QAliasDictionary
     */
    double convert(double value, const QString & in, const QString & out, double defaultValue = NAN) const;

    /**
     * @brief Adds a conversion rule to convertor
     * @param rule rule to add
     * @details This function doesn't convert an alas for a unit to an actual unit name, so make sure to
     * pass here an actual unit name
     * @throw std::invalid_argument if a passed rule has existing family with different base unit,
     * existing unit with different family or existing unit with a different family or base unit
     */
    void addConversionRule(const QUnitConversionRule & rule);

    /**
     * @brief Clears unit convertor removing all unit conversion rules
     */
    void clear();

    /**
     * @brief Method provides access to a list of families of units in this convertor
     * @return QStringList containing a list of unit families
     */
    QStringList families() const;

    /**
     * @brief Gets a family for a given unit
     * @param unit unit to return a family
     * @return a family name or an empty string if unit is unknown to convertor
     */
    QString family(const QString & unit) const;

    /**
     * @brief Gets a list of units with a possible connection to/from a given unit
     * @param unit unit to get a list of conversions
     * @return QStringList with units with possible conversion to a given unit, including a given unit. If
     * conversion to/from a given unit is unknown returns an empty list
     */
    QStringList conversions(const QString & unit) const;

    /**
     * @brief Method provides access to a list of units in this convertor within a given
     * family, effectively providing a list of unit with a possible conversion from
     * any unit of this list to any other
     * @param family family to return unit list
     * @return QStringList containing a list of units known by this unit convertor
     */
    QStringList units(const QString &family) const;

    /**
     * @brief adds aliases from the object QAliasDictionary
     */
    void setAliases(QAliasDictionary<QString> aliases);

    /**
     * @brief adds one alias
     */
    void addAlias(QString name, QString alias);


    /**
     * @brief Removes all alias rules
     */
    void clearAliases();

    /**
     * @brief Gets unit name by alias using internal alias dictionary
     * @param alias unit alias to get unit name
     * @return unit name or an empty string if a specified alias is not found
     */
    QString unitName(const QString & alias) const;

protected:
    QMap <QString, QString> m_familiesByUnit;   ///< Key is a unit, Value is a corresponding family. Base units are also put here
    QMap <QString, QString> m_baseUnitsByFamilies;  ///< Key is a family name, Value is a corresponding base unit
    QMap <QString, QUnitConversionFamily> m_families;   ///< Key is a family name, Value is a family
    QAliasDictionary<QString> m_aliases;
};

#endif // QUNITCONVERTOR_H
