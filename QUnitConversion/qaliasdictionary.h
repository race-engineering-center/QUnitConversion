#ifndef QALIASDICTIONARY_H
#define QALIASDICTIONARY_H

#include <QMap>
#include <QDebug>

/**
 * @brief The QAliasDictionary class provides
 * an alias dictionary to allow quick on-the-fly
 * conversion of unit name aliases such as
 * km/h -> kmph, kmh etc.
 */
template<class String>
class QAliasDictionary
{
public:
    /**
     * @brief Gets name by alias
     * @param alias to get name
     * @return string containing name corresponding to the given alias
     */
    String name(const String &alias) const
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
    QList<String> aliases(const String &name) const
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
    void addAlias(String name, String alias)
    {
        m_aliases.insert(std::move(alias), name);
        m_names.insert(std::move(name));
    }
    /**
     * @brief Checks if a dictionary contains name for the given alias
     * @param alias alias to check existence
     * @return true if a dictionary contains name for the given alias, false otherwise
     */
    bool contains(const String &alias) const
    {
        if (m_names.contains(alias))
            return true;
        return m_aliases.contains(alias);
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
    QMap<String, String> m_aliases;
    QSet<String> m_names;
};

#endif // QALIASDICTIONARY_H
