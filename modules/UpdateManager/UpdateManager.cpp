//
// Created by CatMoe on 2022/7/11.
//

#include "UpdateManager.h"
#include "../ConfigManager/ConfigManager.h"
#include "../Utils/httplib.h"
#include "../Utils/json.hpp"
#include <iostream>

void UpdateManager::UpdateManagerInit() {
    // 检查KatBoot版本
    std::cout << "Checking for KatBoot updates" << std::endl;
    std::string newKatBootVersion = checkUpdate(ConfigManager::KAT_BOOT_REPO_BASE_URL);
    if (newKatBootVersion != ConfigManager::KAT_BOOT_VERSION) {
        std::cout << "New KatBoot version " << newKatBootVersion << " found" << std::endl;
        doKatBootUpdate(newKatBootVersion);
    } else {
        std::cout << "You have the latest KatBoot version " << ConfigManager::KAT_BOOT_VERSION << std::endl;
    }

    // 检查KatServer版本
    std::cout << "Checking for KatServer updates" << std::endl;
    std::string newKatServerVersion = checkUpdate(ConfigManager::KAT_SERVER_REPO_BASE_URL);
    if (newKatServerVersion != ConfigManager::KAT_SERVER_VERSION) {
        std::cout << "New KatServer version " << newKatServerVersion << " found" << std::endl;
        doKatServerUpdate(newKatServerVersion);
    } else {
        std::cout << "You have the latest KatServer version " << ConfigManager::KAT_SERVER_VERSION << std::endl;
    }
}

std::string UpdateManager::checkUpdate(std::string repo) {
    httplib::Client client("https://api.github.com");
    auto response = client.Get(("/repos" + repo + "/releases/latest").c_str());
    nlohmann::json jsonBody = nlohmann::json::parse(response->body);
    return jsonBody["tag_name"];
}

void UpdateManager::doKatBootUpdate(std::string version) {

}

void UpdateManager::doKatServerUpdate(std::string version) {

}