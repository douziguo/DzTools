/******************************************************************************
 * Copyright(C) 2025 Dzg Robotics Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       DalsaCameraInstance.cpp
 * @brief      单例，用于维护全局的 Dalsa 相关实例
 *
 * @author     douziguo<ziguodou@gemail.com>
 * @date       2025/04/13
 *
 * @history
 * - 2025/04/13 模块创建
 *****************************************************************************/

#include "DalsaCameraInstance.h"

#include <QDebug>

namespace DzCamera {

DalsaCameraInstance::DalsaCameraInstance()
{
    // This prevents unnecessary unloading and reloading of the Sapera LT libraries
    // during execution of this program
    SapManager::Open();

    // Register callback to be notified of camera connection and disconnection events
    // SapManager::RegisterServerCallback(SapManager::EventServerNew | SapManager::EventServerDisconnected | SapManager::EventServerConnected | SapManager::EventResourceInfoChanged, ServerCallback, NULL);

    SapManager::SetDisplayStatusMode(SapManager::StatusLog);

    SapManager::SetCommandTimeout(1200000);
}

DalsaCameraInstance::~DalsaCameraInstance()
{
    SapManager::UnregisterServerCallback();
    SapManager::Close();
}

}   // namespace DzCamera
