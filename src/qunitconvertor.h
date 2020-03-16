#ifndef QUNITCONVERTOR_H
#define QUNITCONVERTOR_H

#include <QJsonObject>

#include <math.h>

#include "qlinearfunction.h"

/**
 * @brief The QUnitConvertor class provides tool for converting units stored
 * in a string form. It uses "base" unit for each "family" (length, speed etc)
 * and perform conversions inside a family through conversion to and from base unit.
 */
class QUnitConvertor
{
public:
    /**
     * @brief Default constructor
     */
    QUnitConvertor();

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
     * @return value converted to
     */
    double convert(double value, const QString & in, const QString & out) const;

    /**
     * @brief Deserializes unit conversion rules from JSON
     * @param json JSON object for deserialization
     */
    void loadFromJson(const  & json);

    /**
     * @brief Serializes current unit conversion rules to JSON
     * @return QJsonObject containing serialized rules
     */
    QJsonObject toJson() const;


};

#endif // QUNITCONVERTOR_H
