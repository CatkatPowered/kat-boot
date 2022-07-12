//
// Created by CatMoe on 2022/7/11.
//

#ifndef KAT_BOOT_CONFIGMANAGER_H
#define KAT_BOOT_CONFIGMANAGER_H

#include <string>
#include "../Utils/toml.h"

class ConfigManager {
public:
    static std::string KAT_BOOT_REPO_BASE_URL;
    static std::string KAT_SERVER_REPO_BASE_URL;
    static std::string KAT_BOOT_VERSION;
    static std::string KAT_SERVER_VERSION;

private:
    static toml::table loadConfig();
};


#endif //KAT_BOOT_CONFIGMANAGER_H
