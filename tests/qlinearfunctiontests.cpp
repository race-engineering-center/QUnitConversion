#include "qlinearfunctiontests.h"

QLinearFunctionTests::QLinearFunctionTests(QObject *parent) : QObject(parent)
{

}

void QLinearFunctionTests::basisTests()
{
    QLinearFunction function;
    QVERIFY(!function.isValid());
    QVERIFY(qFuzzyIsNull(function.k()));
    QVERIFY(qFuzzyIsNull(function.b()));

    function.setK(15);
    function.setB(5);
    QVERIFY(function.isValid());
    QVERIFY(qFuzzyCompare(function.k(), 15));
    QVERIFY(qFuzzyCompare(function.b(), 5));

    QLinearFunction secondFunction(1, 2);
    QVERIFY(secondFunction.isValid());
    QVERIFY(qFuzzyCompare(secondFunction.k(), 1));
    QVERIFY(qFuzzyCompare(secondFunction.b(), 2));
}

void QLinearFunctionTests::valueTest()
{
    QLinearFunction function(5.5, 3);
    QVERIFY(function.isValid());
    QVERIFY(qFuzzyCompare(function.y(0), 3));
    QVERIFY(qFuzzyCompare(function.y(-5), -24.5));
    QVERIFY(qFuzzyCompare(function.y(1), 8.5));
    QVERIFY(qFuzzyCompare(function.y(0.7659), 7.21245));
    QVERIFY(qFuzzyCompare(function.y(35.6), 198.8));
}

void QLinearFunctionTests::inversedTest()
{
    QLinearFunction function(3, -2);
    function = function.inversed();
    QVERIFY(qFuzzyCompare(function.k(), double(1) / 3));
    QVERIFY(qFuzzyCompare(function.b(), double(2) / 3));

    function.setK(-2);
    function.setB(-16);
    function = function.inversed();
    QVERIFY(qFuzzyCompare(function.k(), -0.5));
    QVERIFY(qFuzzyCompare(function.b(), -8));
}
