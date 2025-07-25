/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       SentechInstance.cpp
 * @brief      单例，用于维护全局的 Sentech 相关实例
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2021/04/13
 *
 * @history
 * - 2021/04/13 模块创建
 *****************************************************************************/

#include "SentechInstance.h"

#include <QImage>
#include <QDebug>

namespace SpeedCamera {

using namespace StApi;

SentechInstance::SentechInstance()
{
    StApiInitialize();

    try {
        pIStSystem = CreateIStSystem(StSystemVendor_Default, StInterfaceType_GigEVision);
    } catch (const GenICam::GenericException &e) {
        qDebug() << "无法获取取图系统：" << e.GetDescription();
    }
}

SentechInstance::~SentechInstance()
{
    releaseIStSystemPtr();
    StApiTerminate();
}

// 获取取图系统，用于设备扫描和连接
StApi::IStSystemReleasable *SentechInstance::getIStSystemPtr()
{
    return pIStSystem;
}

// 释放取图系统
void SentechInstance::releaseIStSystemPtr()
{
    /*
     * 是的，這部份的架構是完全沿用GenTL的架構，
     * 因此宣告的元件要是沒有Release的話，其它程序或相同程序內是無法再次宣告並存取的。
     * 這也是為什麼同樣用GenTL為基底的SDK無法同時使用的原因。
     *
     * IStsystem – 整個取圖系統
     * IStInterface – 介面(U3V/GigE/CoaX)
     * IStDevice – 相機個體
     *
     * 寫程序時元件的Lifetime這部份需要留意。
     */
    if (pIStSystem != nullptr) {
        pIStSystem->Release();
    }
}

}   // namespace SpeedCamera
