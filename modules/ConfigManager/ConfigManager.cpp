//
// Created by CatMoe on 2022/7/11.
//

#include "ConfigManager.h"
#include <string>
#include <iostream>
#include "../Utils/toml.h"


// TODO: 把这个测试用的repo url替换掉（但估计得等我们发布第一个beta了
std::string ConfigManager::KAT_BOOT_REPO_BASE_URL = "/yhirose/cpp-httplib";
std::string ConfigManager::KAT_SERVER_REPO_BASE_URL = "/yhirose/cpp-httplib";
std::string ConfigManager::KAT_BOOT_VERSION = loadConfig()["boot"]["kat_boot_version"].value<std::string>().value();
std::string ConfigManager::KAT_SERVER_VERSION = loadConfig()["boot"]["kat_server_version"].value<std::string>().value();

toml::table ConfigManager::loadConfig() {
    // 读取本地配置文件获取版本
    return toml::parse_file("./KatBootConfig.toml");
}