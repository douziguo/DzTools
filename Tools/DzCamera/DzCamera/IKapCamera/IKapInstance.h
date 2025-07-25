#ifndef IKAPINSTANCE_H
#define IKAPINSTANCE_H

#pragma execution_character_set("utf-8")

#include <QObject>

#include "IKap/Include/IKapBoard.h"
#include "IKap/Include/IKapC.h"

namespace SpeedCamera {

class IKapInstance
{
public:
    explicit IKapInstance();
    ~IKapInstance();

    static QString formatErrorMsg(uint32_t res, const QString &msg = QString());
    static QString formatBoardErrorMsg(int res, const QString &msg = QString());
};

} // namespace SpeedCamera

#endif // IKAPINSTANCE_H
