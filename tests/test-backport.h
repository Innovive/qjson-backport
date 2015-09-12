
#include <QtCore>

#ifndef TEST_BACKPORT
#define TEST_BACKPORT

#define Q_TESTLIB_EXPORT Q_DECL_IMPORT
#define Q_DECL_OVERRIDE override

#ifdef QT_TESTCASE_BUILDDIR
# define QFINDTESTDATA(basepath)\
    QTest5::qFindTestData(basepath, __FILE__, __LINE__, QT_TESTCASE_BUILDDIR)
#else
# define QFINDTESTDATA(basepath)\
    QTest5::qFindTestData(basepath, __FILE__, __LINE__)
#endif

namespace QTest5
{

    Q_TESTLIB_EXPORT QString qFindTestData(const char* basepath, const char* file = 0, int line = 0, const char* builddir = 0);
    Q_TESTLIB_EXPORT QString qFindTestData(const QString& basepath, const char* file = 0, int line = 0, const char* builddir = 0);

}

#endif