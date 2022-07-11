//
// Created by CatMoe on 2022/7/11.
//

#include "ConfigManager.h"
#include <string>

// TODO: 把这个测试用的repo url替换掉（但估计得等我们发布第一个beta了
std::string ConfigManager::REPO_BASE_URL = "/yhirose/cpp-httplib";
std::string ConfigManager::VERSION = ConfigManager::getVersion();

std::string ConfigManager::getVersion() {
    // TODO: 读取本地配置文件获取版本
}