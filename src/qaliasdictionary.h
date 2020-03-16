#ifndef QALIASDICTIONARY_H
#define QALIASDICTIONARY_H

#include <QMap>

/**
 * @brief The QAliasDictionary class provides
 * an alias dictionary to allow quick on-the-fly
 * conversion of unit name aliases such as
 * km/h -> kmph, kmh etc.
 */
class QAliasDictionary
{
public:
    /**
     * @brief Default constructor
     */
    QAliasDictionary();

    /**
     * @brief Gets name by alias
     * @param alias to get name
     * @return string containing name corresponding to the given alias
     */
    QString name(const QString & alias) const;

    /**
     * @brief Gets a list of aliases for a given name
     * @param name name to get aliases
     * @return QList<QString> containing aliases for a given name
     */
    QList<QString> aliases(const QString & name) const;

    /**
     * @brief Checks if this dictionary is empty
     * @return true if empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * @brief Adds an alias to the dictionary
     * @param name name which will be returned if an alias requested
     * @param alias alias for the given name
     */
    void addAlias(const QString & name, const QString & alias);



protected:
    QMap <QString, QString> m_aliases;
};

#endif // QALIASDICTIONARY_H
