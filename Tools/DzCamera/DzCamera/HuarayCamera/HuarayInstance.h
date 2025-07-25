#ifndef HUARAYINSTANCE_H
#define HUARAYINSTANCE_H

#pragma execution_character_set("utf-8")

#include <QObject>

#include <IMVApi.h>
#include <IMVDefines.h>

class HuarayInstance : public QObject
{
    Q_OBJECT
public:
    HuarayInstance();
    ~HuarayInstance();

    static QString formatErrorMsg(int nErrorNum, const QString &msg = QString());
    static void frameToImage(void* handle, const IMV_Frame& frame, QImage& image);
};

#endif // HUARAYINSTANCE_H
