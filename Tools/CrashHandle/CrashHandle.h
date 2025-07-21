//
// Created by douziguo on 25-7-14.
//
/***
 * 崩溃捕获
 *
 * 参考资料：
 * - https://blog.csdn.net/lanhy999/article/details/12189375
 * - https://blog.csdn.net/xiezhongyuan07/article/details/86491460
 * - https://blog.csdn.net/w54a3teg64c7bd/article/details/108993208
 * - https://www.cnblogs.com/FKdelphi/p/10731775.html
 */

#ifndef DZTOOLS_CRASHHANDLE_H
#define DZTOOLS_CRASHHANDLE_H

// 指定文件编码，防止中文乱码
#pragma execution_character_set("utf-8")

#include <QtCore/QtGlobal>

#ifndef QAPPLICATION_CLASS
#define QAPPLICATION_CLASS QCoreApplication
#endif

#include QT_STRINGIFY(QAPPLICATION_CLASS)

#ifndef CRASH_NO_DIALOG
#include <QMessageBox>
#endif
#include <QDateTime>
#include <QDir>

#include <windows.h>
#include <Dbghelp.h>

// 崩溃 dump 文件输出目录
#ifndef CRASH_PATH
#define CRASH_PATH "dump"
#endif

static LONG WINAPI exceptionCallback(struct _EXCEPTION_POINTERS *exceptionInfo)
{
    QString savePath = CRASH_PATH;

    // 路径优化
    savePath.append(QDir::separator());
    savePath = QDir::toNativeSeparators(savePath).replace("\\\\", "\\").replace("//", "/");

    QDir dir(savePath);
    if (!dir.exists() && !dir.mkpath(savePath)) {
        exit(E_UNEXPECTED);
        return EXCEPTION_EXECUTE_HANDLER;
    }

    savePath.append("crash_");
    savePath.append(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss.zzz"));
    savePath.append(".dmp");

    HANDLE dump = CreateFileW(
            savePath.toStdWString().c_str(),
            GENERIC_WRITE,
            0,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    if (INVALID_HANDLE_VALUE == dump) {
        exit(E_UNEXPECTED);
        return EXCEPTION_EXECUTE_HANDLER;
    }

    MINIDUMP_EXCEPTION_INFORMATION miniDumpExceptionInfo;
    miniDumpExceptionInfo.ExceptionPointers = exceptionInfo;
    miniDumpExceptionInfo.ThreadId = GetCurrentThreadId();
    miniDumpExceptionInfo.ClientPointers = TRUE;
    DWORD idProcess = GetCurrentProcessId();
    MiniDumpWriteDump(
            GetCurrentProcess(), idProcess, dump, MiniDumpNormal, &miniDumpExceptionInfo, NULL, NULL);

    CloseHandle(dump);

#ifndef CRASH_NO_DIALOG
    // 这里弹出一个错误对话框并退出程序
    EXCEPTION_RECORD *record = exceptionInfo->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode, 16)),
            errAdr(QString::number((uint) record->ExceptionAddress, 16)), errMod;
    QMessageBox::critical(
            nullptr,
            "Ooops!",
            "<font size=4><div><b>出现了一些无法处理的异常，程序即将退出……</b><br/></div>"
            + QString("<div>错误代码：0x%1</div><div>错误地址：0x%2</div></font>")
                    .arg(errCode.toUpper())
                    .arg(errAdr.toUpper()),
            QMessageBox::Ok);
#endif

    exit(E_UNEXPECTED);
    return EXCEPTION_EXECUTE_HANDLER;
}

// 初始化崩溃捕获
void initCrashHandle()
{
    SetUnhandledExceptionFilter(exceptionCallback);
}

#endif //DZTOOLS_CRASHHANDLE_H
