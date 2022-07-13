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

// TODO: 为katserver和katboot放出一个release进行测试
// WARNING: 以下代码未进行测试！！
void UpdateManager::doKatBootUpdate(std::string version) {
#ifdef linux
    std::string fileName = "kat-boot";
#endif
#ifdef _WIN32
    std::string fileName = "kat-boot.exe";
#endif
    httplib::Client client("https://api.github.com");
    auto response = client.Get(("/repos" + ConfigManager::KAT_BOOT_REPO_BASE_URL + "/releases/latest").c_str());

    nlohmann::json jsonBody = nlohmann::json::parse(response->body);
    std::string downloadPath;
    for (int i = 0; i < jsonBody["assets"].size(); ++i) {
        if (jsonBody["assets"][i]["name"] != fileName) {
            continue;
        } else {
            downloadPath = jsonBody["assets"][i]["browser_download_url"].get<std::string>().erase(0, 17);
            break;
        }
    }
    httplib::Client downloadClient("https://github.com");
    std::ofstream file(fileName, std::ofstream::binary);
    auto downloadResponse = downloadClient.Get(downloadPath.c_str(),
                                               [&](const char *data, size_t data_length) {
                                                   file.write(data, data_length);
                                                   return true;
                                               });
}

void UpdateManager::doKatServerUpdate(std::string version) {
    std::string fileName = "kat-server.jar";
    httplib::Client client("https://api.github.com");
    auto response = client.Get(("/repos" + ConfigManager::KAT_SERVER_REPO_BASE_URL + "/releases/latest").c_str());

    nlohmann::json jsonBody = nlohmann::json::parse(response->body);
    std::string downloadPath;
    for (int i = 0; i < jsonBody["assets"].size(); ++i) {
        if (jsonBody["assets"][i]["name"] != fileName) {
            continue;
        } else {
            downloadPath = jsonBody["assets"][i]["browser_download_url"].get<std::string>().erase(0, 17);
            break;
        }
    }
    httplib::Client downloadClient("https://github.com");
    std::ofstream file(fileName, std::ofstream::binary);
    auto downloadResponse = downloadClient.Get(downloadPath.c_str(),
                                               [&](const char *data, size_t data_length) {
                                                   file.write(data, data_length);
                                                   return true;
                                               });
}