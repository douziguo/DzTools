/******************************************************************************
 * Copyright(C) 2023 Speedbot Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       DahengInstance.cpp
 * @brief      大恒相机 SDK 生命周期管理
 *
 * @author     李孟其<limengqi@email.cn>
 * @date       2023/02/08
 *
 * @history
 * - 2023/02/08 模块创建
 *****************************************************************************/

#include "DahengInstance.h"

#include "GalaxyIncludes.h"

namespace SpeedCamera {

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
