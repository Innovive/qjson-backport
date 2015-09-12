#include "test-backport.h"

#include <QtTest/qtestcase.h>
// #include <QtTest/qtestassert.h>

// #include <QtCore/qbytearray.h>
// #include <QtCore/qmetaobject.h>
// #include <QtCore/qobject.h>
// #include <QtCore/qstringlist.h>
// #include <QtCore/qvector.h>
// #include <QtCore/qvarlengtharray.h>
// #include <QtCore/qcoreapplication.h>
// #include <QtCore/qfile.h>
// #include <QtCore/qfileinfo.h>
// #include <QtCore/qdir.h>
// #include <QtCore/qprocess.h>
// #include <QtCore/qdebug.h>
// #include <QtCore/qlibraryinfo.h>
// #include <QtCore/private/qtools_p.h>
// #include <QtCore/qdiriterator.h>
// #include <QtCore/qtemporarydir.h>

// #include <QtTest/private/qtestlog_p.h>
// #include <QtTest/private/qtesttable_p.h>
// #include <QtTest/qtestdata.h>
// #include <QtTest/private/qtestresult_p.h>
// #include <QtTest/private/qsignaldumper_p.h>
// #include <QtTest/private/qbenchmark_p.h>
// #include <QtTest/private/cycle_p.h>
// #include <QtTest/private/qtestblacklist_p.h>



/*! \internal
 */

QString QTest5::qFindTestData(const QString& base, const char *file, int line, const char *builddir)
{
    QString found;
	QString mainSourcePath;

    // Testdata priorities:

    //  1. relative to test binary.
    if (qApp) {
        QDir binDirectory(QCoreApplication::applicationDirPath());
        if (binDirectory.exists(base)) {
            found = binDirectory.absoluteFilePath(base);
        }
#ifdef Q_OS_WIN
        // Windows: The executable is typically located in one of the
        // 'Release' or 'Debug' directories.
        else if (isWindowsBuildDirectory(binDirectory.dirName())
                 && binDirectory.cdUp() && binDirectory.exists(base)) {
            found = binDirectory.absoluteFilePath(base);
        }
#endif // Q_OS_WIN
        // else if (QTestLog::verboseLevel() >= 2) {
        //     const QString candidate = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + QLatin1Char('/') + base);
        //     QTestLog::info(qPrintable(
        //         QString::fromLatin1("testdata %1 not found relative to test binary [%2]; "
        //                             "checking next location").arg(base, candidate)),
        //         file, line);
        // }
    }

    //  2. installed path.
    // if (found.isEmpty()) {
    //     const char *testObjectName = QTestResult::currentTestObjectName();
    //     if (testObjectName) {
    //         QString testsPath = QLibraryInfo::location(QLibraryInfo::testsPath);
    //         QString candidate = QString::fromLatin1("%1/%2/%3")
    //             .arg(testsPath, QFile::decodeName(testObjectName).toLower(), base);
    //         if (QFileInfo(candidate).exists()) {
    //             found = candidate;
    //         }
    //         // else if (QTestLog::verboseLevel() >= 2) {
    //         //     QTestLog::info(qPrintable(
    //         //         QString::fromLatin1("testdata %1 not found in tests install path [%2]; "
    //         //                             "checking next location")
    //         //             .arg(base, QDir::toNativeSeparators(candidate))),
    //         //         file, line);
    //         // }
    //     }
    // }

    //  3. relative to test source.
    if (found.isEmpty()) {
        // srcdir is the directory containing the calling source file.
        QFileInfo srcdir = QFileInfo(QFile::decodeName(file)).path();

        // If the srcdir is relative, that means it is relative to the current working
        // directory of the compiler at compile time, which should be passed in as `builddir'.
        if (!srcdir.isAbsolute() && builddir) {
            srcdir.setFile(QFile::decodeName(builddir) + QLatin1String("/") + srcdir.filePath());
        }

        class QString candidate = QString::fromLatin1("%1/%2").arg(srcdir.canonicalFilePath(), base);
        if (QFileInfo(candidate).exists()) {
            found = candidate;
        }
        // else if (QTestLog::verboseLevel() >= 2) {
        //     QTestLog::info(qPrintable(
        //         QString::fromLatin1("testdata %1 not found relative to source path [%2]")
        //             .arg(base, QDir::toNativeSeparators(candidate))),
        //         file, line);
        // }
    }

    // 4. Try resources
    if (found.isEmpty()) {
        class QString candidate = QString::fromLatin1(":/%1").arg(base);
        if (QFileInfo(candidate).exists())
            found = candidate;
    }

    // 5. Try current directory
    if (found.isEmpty()) {
        class QString candidate = QString::fromLatin1("%1/%2").arg(QDir::currentPath()).arg(base);
        if (QFileInfo(candidate).exists())
            found = candidate;
    }

    // 6. Try main source directory
    if (found.isEmpty()) {
        class QString candidate = mainSourcePath % QLatin1Char('/') % base;
        if (QFileInfo(candidate).exists())
            found = candidate;
    }

    if (found.isEmpty()) {
        QTest::qWarn(qPrintable(
            QString::fromLatin1("testdata %1 could not be located!  %2  %3").arg(base).arg(file).arg(line)
        ));
    }
    // else if (QTestLog::verboseLevel() >= 1) {
    //     QTestLog::info(qPrintable(
    //         QString::fromLatin1("testdata %1 was located at %2").arg(base, QDir::toNativeSeparators(found))),
    //         file, line);
    // }

    return found;
}

/*! \internal
 */
QString QTest5::qFindTestData(const char *base, const char *file, int line, const char *builddir)
{
    return qFindTestData(QFile::decodeName(base), file, line, builddir);
}