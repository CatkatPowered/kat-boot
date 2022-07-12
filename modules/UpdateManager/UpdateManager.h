//
// Created by CatMoe on 2022/7/11.
//

#ifndef KAT_BOOT_UPDATEMANAGER_H
#define KAT_BOOT_UPDATEMANAGER_H

#include <string>
class UpdateManager {
    // 初始化更新模块
public:
    static void UpdateManagerInit();
    // 检查是否为最新版本
private:
    static std::string checkUpdate(std::string repo);
    // 下载指定版本
private:
    static void doKatBootUpdate(std::string version);
    static void doKatServerUpdate(std::string version);
};


#endif //KAT_BOOT_UPDATEMANAGER_H
