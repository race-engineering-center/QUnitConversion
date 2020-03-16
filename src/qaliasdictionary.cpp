#include "qaliasdictionary.h"

QAliasDictionary::QAliasDictionary()
{

}

QString QAliasDictionary::name(const QString &alias) const
{
    return m_aliases.value(alias);
}

bool QAliasDictionary::isEmpty() const
{
    return m_aliases.isEmpty();
}

void QAliasDictionary::addAlias(const QString &name, const QString &alias)
{
    m_aliases.insert(alias, name);
}
