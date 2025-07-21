//
// Created by douziguo on 25-7-14.
//

#include "LogBox.h"
#include <QDebug>
#include <QStyle>


/***
 * 日志显示控件
 *
 * 参考资料：
 * - https://bbs.csdn.net/topics/392183067
 * - https://blog.csdn.net/Maybe______/article/details/52997826
 */

LogBox::LogBox(QWidget *parent) : QTextEdit(parent)
{
    /***
    // 另一种修改行高与间距的方案
    QTextCursor textCursor = this->textCursor();
    QTextBlockFormat textBlockFormat;
    textBlockFormat.setLineHeight(200, QTextBlockFormat::FixedHeight);//设置固定行高
    textBlockFormat.setBottomMargin(20);    // 行间距
    textCursor.setBlockFormat(textBlockFormat);
    this->setTextCursor(textCursor);
    **/

    setReadOnly(true);
    setLineFormat("[MM-dd hh:mm:ss.zzz] ...");
    setSkin(Light);

    /***
    log(    "运行日志运行日志运行日志运行日志");
    info(   "运行日志运行日志运行日志");
    warning("运行日志运行日志运行日志运行日志运行日志运行日志");
    danger( "运行日志运行日志运行日志运行日志");
    success("运行日志运行日志");
    log(    "运行日志运行日志运行日志");
    info(   "运行日志运行日志运行日志运行日志");
    warning("运行日志运行日志");
    danger( "运行日志");
    success("运行日志运行日志运行日志");
    ***/
}

// 应用行内的 css（TODO: 应用前清理以前插入的 css）
void LogBox::applyInlineStyleSheet()
{
    // 这样插入无效。。。
    //QTextEdit::append(QString("<style>%1</style>").arg(skinCss + inlineCss));
}

/************************* 对外方法 ******************************/

// 清理日志内容
void LogBox::clear()
{
    QTextEdit::clear();
    applyInlineStyleSheet();
    currentMsgCount = 0;
}

// 普通信息
void LogBox::log(const QString msg, LogBox::LogTypes type)
{
    // 内容超长，自动清理
    if (++currentMsgCount > maxMsgCount) {
        clear();
    }

    QString lineClass;
    switch(type)
    {
        case Normal:  lineClass = "log--normal";  break;  // 普通信息
        case Info:    lineClass = "log--info";    break;  // 提示信息
        case Success: lineClass = "log--success"; break;  // 成功的信息
        case Warning: lineClass = "log--warning"; break;  // 警告信息
        case Danger:  lineClass = "log--danger";  break;  // 危险信息
    }

    QString line = QDateTime::currentDateTime()
            .toString(lineFormat)   // 转义时间
            .replace("...", msg)    // 转义消息
            .replace("\n", "<br>"); // 转义换行

    // 这样使用时，QT 会自动将 style 中的内容转为行内样式
    append(QString("<style>%3%4</style><p class='%1'>%2</p>")
                   .arg(lineClass).arg(line).arg(skinCss).arg(inlineCss));
}

// 提示信息
void LogBox::info(const QString msg)
{
    log(msg, Info);
}

// 成功的信息
void LogBox::success(const QString msg)
{
    log(msg, Success);
}

// 警告信息
void LogBox::warning(const QString msg)
{
    log(msg, Warning);
}

// 危险信息
void LogBox::danger(const QString msg)
{
    log(msg, Danger);
}

// 设置指令行的格式，“...”将被转换为行内容
void LogBox::setLineFormat(QString lineFormat)
{
    this->lineFormat = lineFormat;
}

// 设置皮肤
void LogBox::setSkin(Skin skin)
{
    this->skin = skin;

    QString style =
            "QTextEdit p {line-height: 10%;}"
            "QTextEdit{padding: 2px; background-color:#fff; "
            "} "
            "QScrollBar:horizontal,"
            "QScrollBar:vertical{background:transparent;padding:0;border-radius: 0;}"
            "QScrollBar:horizontal{max-height: 8px;}"
            "QScrollBar:vertical{   max-width: 8px;}"
            "QScrollBar::handle:horizontal,"
            "QScrollBar::handle:vertical{background-color: #dddee0;border-radius: 4px;}"
            "QScrollBar::handle:horizontal{min-width: 50px;}"
            "QScrollBar::handle:vertical {min-height: 50px;}"
            "QScrollBar::handle:horizontal:hover,"
            "QScrollBar::handle:vertical:hover{  background: #c7c9cc;}"
            "QScrollBar::handle:horizontal:pressed,"
            "QScrollBar::handle:vertical:pressed{background: #c7c9cc;}"
            "QScrollBar::add-page:horizontal, QScrollBar::add-page:vertical{background:none;}"
            "QScrollBar::sub-page:horizontal, QScrollBar::sub-page:vertical{background:none;}"
            "QScrollBar::add-line:horizontal, QScrollBar::add-line:vertical{background:none;}"
            "QScrollBar::sub-line:horizontal, QScrollBar::sub-line:vertical{background:none;}"
            "QScrollArea{border:none;}";

    switch (skin) {
        case Dark:
            style += "QScrollBar::handle:horizontal,"
                     "QScrollBar::handle:vertical{background:#525252;}"
                     "QScrollBar::handle:horizontal:hover,"
                     "QScrollBar::handle:vertical:hover{background:#6d6d6d;}"
                     "QScrollBar::handle:horizontal:pressed,"
                     "QScrollBar::handle:vertical:pressed{background:#7b7b7b;}"
                     "QTextEdit{border:1px solid #242424; background: rgb(43,43,43);} ";

            skinCss = QString(
                    ".log--normal  { color: %1 }"
                    ".log--info    { color: %2 }"
                    ".log--success { color: %3 }"
                    ".log--warning { color: %4 }"
                    ".log--danger  { color: %5 }"
            )
                    .arg("gray")
                    .arg("rgb(100, 184, 255)")
                    .arg("rgb(14, 126, 18)")
                    .arg("rgb(241, 105, 32)")
                    .arg("rgb(255, 107, 107)");
            break;

        case Light:
            skinCss = QString(
                    ".log--normal  { color: %1 }"
                    ".log--info    { color: %2 }"
                    ".log--success { color: %3 }"
                    ".log--warning { color: %4 }"
                    ".log--danger  { color: %5 }"
            )
                    .arg("#606266")
                    .arg("#909399")
                    .arg("#67C23A")
                    .arg("#E6A23C")
                    .arg("#F56C6C");
            break;

        case Pure:
            skinCss = "p { color: #606266 }";
            break;
    }
    skinCss += "p { line-height: 1.2; margin: 0 0 4px; }";

    //style().

    setStyleSheet(style);
    applyInlineStyleSheet();
}

// 设置行内的 CSS 布局
void LogBox::setInlineStyleSheet(QString css)
{
    inlineCss = css;
    applyInlineStyleSheet();
}