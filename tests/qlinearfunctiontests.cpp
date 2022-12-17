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

void QLinearFunctionTests::combinedTest()
{
    QLinearFunction cToK(1, 273.15);
    QLinearFunction KToF(1.8, -459.67);
    QLinearFunction combined = QLinearFunction::combined(cToK, KToF);
    // an underlying conversion is in /tests/C_to_F.xlsx file
    QVERIFY(qFuzzyCompare(combined.y(-273.15), -459.67));
    QVERIFY(qFuzzyCompare(combined.y(-45.56), -50.008));
    QVERIFY(qFuzzyCompare(combined.y(-40), -40));
    QVERIFY(qFuzzyCompare(combined.y(-34.44), -29.992));
    QVERIFY(qFuzzyCompare(combined.y(-28.89), -20.002));
    QVERIFY(qFuzzyCompare(combined.y(-23.33), -9.994));
    QVERIFY(qFuzzyCompare(combined.y(-12.22), 10.004));
    QVERIFY(qFuzzyCompare(combined.y(-6.67), 19.994));
    QVERIFY(qFuzzyCompare(combined.y(-1.11), 30.002));
    QVERIFY(qFuzzyCompare(combined.y(0), 32));
    QVERIFY(qFuzzyCompare(combined.y(4.44), 39.992));
    QVERIFY(qFuzzyCompare(combined.y(10), 50));
    QVERIFY(qFuzzyCompare(combined.y(60), 140));
    QVERIFY(qFuzzyCompare(combined.y(65.56), 150.008));
    QVERIFY(qFuzzyCompare(combined.y(100), 212));
    QVERIFY(qFuzzyCompare(combined.y(260), 500));
    QVERIFY(qFuzzyCompare(combined.y(537.78), 1000.004));


}
