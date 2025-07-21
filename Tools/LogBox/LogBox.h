//
// Created by douziguo on 25-7-14.
//

#ifndef DZTOOLS_LOGBOX_H
#define DZTOOLS_LOGBOX_H


#include <QTextEdit>
#include <QDateTime>

class LogBox : public QTextEdit
{
Q_OBJECT
    Q_ENUMS(LogTypes)

public:
    // 设置皮肤
    enum Skin {
        Dark,           // 黑暗皮肤
        Light,          // 浅色皮肤
        Pure            // 纯粹
    };

    // 消息类型
    enum LogTypes {
        Normal,         // 普通信息
        Info,           // 提示信息
        Success,        // 成功的信息
        Warning,        // 警告信息
        Danger,         // 危险信息
    };

private:
    int currentMsgCount = 0, maxMsgCount = 500;
    QString lineFormat;
    QString inlineCss, skinCss;
    Skin skin = Dark;
public:
    explicit LogBox(QWidget *parent = nullptr);

    void clear();

    void log(const QString msg, LogBox::LogTypes type = Normal);
    void info(const QString msg);
    void success(const QString msg);
    void warning(const QString msg);
    void danger(const QString msg);

    void setInlineStyleSheet(QString css);
    void setLineFormat(QString lineFormat);
    void setSkin(Skin skin);
private:
    void applyInlineStyleSheet();
};


#endif //DZTOOLS_LOGBOX_H
