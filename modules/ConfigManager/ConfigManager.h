//
// Created by CatMoe on 2022/7/11.
//

#ifndef KAT_BOOT_CONFIGMANAGER_H
#define KAT_BOOT_CONFIGMANAGER_H

#include <string>

class ConfigManager {
public:
    static std::string REPO_BASE_URL;
    static std::string VERSION;

private:
    static std::string getVersion();
};


#endif //KAT_BOOT_CONFIGMANAGER_H
