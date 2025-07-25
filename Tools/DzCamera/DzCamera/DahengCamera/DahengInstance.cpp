/******************************************************************************
 * Copyright(C) 2025 Dzg Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       DahengInstance.cpp
 * @brief      大恒相机 SDK 生命周期管理
 *
 * @author     douziguo<ziguodou@gemail.com>
 * @date       2025/04/13
 *
 * @history
 * - 2025/04/13 模块创建
 *****************************************************************************/

#include "DahengInstance.h"

#include "inc/GalaxyIncludes.h"

namespace DzCamera {

DahengInstance::DahengInstance()
{
    // 使用其他接口之前，必须执行初始化
    IGXFactory::GetInstance().Init();
}

DahengInstance::~DahengInstance()
{
    // 关闭设备之后，不能再调用其他任何库接口
    IGXFactory::GetInstance().Uninit();
}

}   // namespace SpeedCamera
