QT -= gui
QT += testlib

CONFIG += c++11 console
CONFIG -= app_bundle

CONFIG(debug, debug|release): BUILD_TYPE = debug
CONFIG(release, debug|release): BUILD_TYPE = release
PLATFORM = $$join(QMAKE_PLATFORM, _,)

DESTDIR = $$PWD/../build_$${QT_VERSION}_$${PLATFORM}_$${QMAKE_COMPILER}_$${QT_ARCH}_$${BUILD_TYPE}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(QUnitConversion.pri)

SOURCES += \
        main.cpp \
        tests/qaliasdictionarytests.cpp \
        tests/qlinearfunctiontests.cpp \
        tests/qunitconvertortests.cpp

HEADERS += \
    tests/qaliasdictionarytests.h \
    tests/qlinearfunctiontests.h \
    tests/qunitconvertortests.h

