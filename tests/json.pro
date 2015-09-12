TARGET = tst_json
QT = core testlib
CONFIG -= app_bundle
CONFIG += testcase
CONFIG += parallel_test

!android:TESTDATA += test.json test.bjson test3.json test2.json
    else:RESOURCES += json.qrc

TESTSRCDIR = .
JSONSRCDIR = ..

INCLUDEPATH += $${TESTSRCDIR} $${JSONSRCDIR}

SOURCES += tst_qtjson.cpp
#HEADERS += $${TESTSRCDIR}/qtestcase.h
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
DEFINES += Q_COMPILER_INITIALIZER_LISTS=1

QMAKE_CXXFLAGS = -mmacosx-version-min=10.7 -std=c++11 -stdlib=libc++ -Wno-deprecated-register

SOURCES += $${JSONSRCDIR}/qjsonwriter.cpp \
    $${JSONSRCDIR}/qjsonvalue.cpp \
    $${JSONSRCDIR}/qjsonparser.cpp \
    $${JSONSRCDIR}/qjsonobject.cpp \
    $${JSONSRCDIR}/qjsondocument.cpp \
    $${JSONSRCDIR}/qjsonarray.cpp \
    $${JSONSRCDIR}/qjson.cpp

HEADERS += $${JSONSRCDIR}/qjsonwriter_p.h \
    $${JSONSRCDIR}/qjsonvalue.h \
    $${JSONSRCDIR}/qjsonparser_p.h \
    $${JSONSRCDIR}/qjson_p.h \
    $${JSONSRCDIR}/qjsonobject.h \
    $${JSONSRCDIR}/qjsonexport.h \
    $${JSONSRCDIR}/qjsondocument.h \
    $${JSONSRCDIR}/qjsonarray.h

CONFIG += debug