#ifndef QUNITCONVERTORTESTS_H
#define QUNITCONVERTORTESTS_H

#include <QtTest>
#include <QCoreApplication>

#include "qunitconvertor.h"

class QUnitConvertorTests : public QObject
{
    Q_OBJECT
public:
    explicit QUnitConvertorTests(QObject *parent = nullptr);

private slots:
    void addRuleTest();
    void setAliasesTest();
    void addAliasTest();
};

#endif // QUNITCONVERTORTESTS_H
