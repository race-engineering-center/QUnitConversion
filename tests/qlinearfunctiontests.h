#ifndef QLINEARFUNCTIONTESTS_H
#define QLINEARFUNCTIONTESTS_H

#include <QtTest>

#include "qlinearfunction.h"

class QLinearFunctionTests : public QObject
{
    Q_OBJECT
public:
    explicit QLinearFunctionTests(QObject *parent = nullptr);

private slots:
    void basisTests();
    void valueTest();
    void inversedTest();

};

#endif // QLINEARFUNCTIONTESTS_H
