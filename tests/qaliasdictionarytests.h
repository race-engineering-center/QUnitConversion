#ifndef QALIASDICTIONARYTESTS_H
#define QALIASDICTIONARYTESTS_H

#include <QtTest>

#include "qaliasdictionary.h"

class QAliasDictionaryTests : public QObject
{
    Q_OBJECT
public:
    explicit QAliasDictionaryTests(QObject *parent = nullptr);

private slots:
    void basicTests();

};

#endif // QALIASDICTIONARYTESTS_H
