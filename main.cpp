#include <QCoreApplication>

#include "iostream"

#include "tests/qlinearfunctiontests.h"
#include "tests/qaliasdictionarytests.h"
#include "tests/qunitconvertortests.h"

#define RUN_TESTS(x) {x member; result += QTest::qExec(&member, argc, argv); std::cout << std::endl; QThread::msleep(100); }

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)
    int result = 0;

    RUN_TESTS(QLinearFunctionTests);
    RUN_TESTS(QAliasDictionaryTests);
    RUN_TESTS(QUnitConvertorTests);

    if (result == 0)
        qDebug()<<"all tests passed succesfully";
    else
        qDebug()<<"tests failed";
}
