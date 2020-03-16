#include <QCoreApplication>

#include "iostream"

#include "tests/qlinearfunctiontests.h"
#include "tests/qaliasdictionarytests.h"

#define RUN_TESTS(x) {x member; result += QTest::qExec(&member, argc, argv); std::cout << std::endl; QThread::msleep(100); }

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    int result = 0;

    RUN_TESTS(QLinearFunctionTests);
    RUN_TESTS(QAliasDictionaryTests);

    if (result == 0)
        qDebug()<<"all tests passed succesfully";
    else
        qDebug()<<"tests failed";
}
