#ifndef QALIASDICTIONARY_H
#define QALIASDICTIONARY_H

#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

/**
 * @brief The QAliasDictionary class provides
 * an alias dictionary to allow quick on-the-fly
 * conversion of unit name aliases such as
 * km/h -> kmph, kmh etc.
 */
template<template<class...> class Map, template<class...> class Set>
class QAliasDictionary
{
public:
    /**
     * @brief Gets name by alias
     * @param alias to get name
     * @return string containing name corresponding to the given alias
     */
    QString name(const QString &alias) const
    {
        if (m_names.contains(alias))
            return alias;
        return m_aliases.value(alias);
    }
    /**
     * @brief Gets a list of aliases for a given name
     * @param name name to get aliases
     * @return QList<QString> containing aliases for a given name
     */
    QList<QString> aliases(const QString &name) const
    {
        return m_aliases.keys(name);
    }
    /**
     * @brief Checks if this dictionary is empty
     * @return true if empty, false otherwise
     */
    bool isEmpty() const
    {
        return m_aliases.isEmpty();
    }
    /**
     * @brief Adds an alias to the dictionary
     * @param name name which will be returned if an alias requested
     * @param alias alias for the given name
     */
    void addAlias(const QString &name, const QString &alias)
    {
        m_aliases.insert(alias, name);
        m_names.insert(name);
    }
    /**
     * @brief Checks if a dictionary contains name for the given alias
     * @param alias alias to check existence
     * @return true if a dictionary contains name for the given alias, false otherwise
     */
    bool contains(const QString &alias) const
    {
        if (m_names.contains(alias))
            return true;
        return m_aliases.contains(alias);
    }
    /**
     * @brief Loads alias rules from JSON
     * @param object object containing serialized dictionary
     */
    void loadFromJson(const QJsonObject &object)
    {
        QJsonArray rules = object["aliases"].toArray();
        for (const auto & r: std::as_const(rules))
        {
            QJsonObject rule = r.toObject();
            QString name = rule["name"].toString();
            if (name.isEmpty())
                continue;
            auto aliases = rule["aliases"].toArray();
            for (const auto & alias: std::as_const(aliases))
                addAlias(name, alias.toString());
        }
    }
    /**
     * @brief Removes all alias-name from dictionary
     */
    void clear()
    {
        m_aliases.clear();
        m_names.clear();
    }

protected:
    Map<QString, QString> m_aliases;
    Set<QString> m_names;
};

#endif // QALIASDICTIONARY_H
