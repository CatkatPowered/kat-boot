//
// Created by CatMoe on 2022/7/11.
//

#ifndef KAT_BOOT_UPDATEMANAGER_H
#define KAT_BOOT_UPDATEMANAGER_H

#include <string>
class UpdateManager {
    // 初始化更新模块
public:
    void UpdateManagerInit();
    // 检查是否为最新版本
private:
    std::string checkUpdate();
    // 下载指定版本
private:
    void doUpdate(std::string commitHash);
};


#endif //KAT_BOOT_UPDATEMANAGER_H
