#include "qaliasdictionary.h"

QAliasDictionary::QAliasDictionary()
{

}

QString QAliasDictionary::name(const QString &alias) const
{
    if (m_names.contains(alias))
        return alias;
    return m_aliases.value(alias);
}

QList<QString> QAliasDictionary::aliases(const QString &name) const
{
    return m_aliases.keys(name);
}

bool QAliasDictionary::isEmpty() const
{
    return m_aliases.isEmpty();
}

void QAliasDictionary::addAlias(const QString &name, const QString &alias)
{
    m_aliases.insert(alias, name);
    m_names.insert(name);
}

bool QAliasDictionary::contains(const QString &alias) const
{
    if (m_names.contains(alias))
        return true;
    return m_aliases.contains(alias);
}

void QAliasDictionary::loadFromJson(const QJsonObject &object)
{
    QJsonArray rules = object["aliases"].toArray();
    for (const auto & r: rules)
    {
        QJsonObject rule = r.toObject();
        QString name = rule["name"].toString();
        if (name.isEmpty())
            continue;
        auto aliases = rule["aliases"].toArray();
        for (const auto & alias: aliases)
            addAlias(name, alias.toString());
    }
}

void QAliasDictionary::clear()
{
    m_aliases.clear();
    m_names.clear();
}
