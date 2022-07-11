//
// Created by CatMoe on 2022/7/11.
//

#include "UpdateManager.h"
#include "../ConfigManager/ConfigManager.h"
#include "../Utils/httplib.h"
#include "../Utils/json.hpp"
#include <iostream>

void UpdateManager::UpdateManagerInit() {
    std::cout << "Checking for updates" << std::endl;
    std::string newVersion = checkUpdate();
    if (newVersion != ConfigManager::VERSION) {
        std::cout << "New version " << newVersion << " found" << std::endl;
        doUpdate(newVersion);
    } else {
        std::cout << "You have the latest version" << std::endl;
    }
}

std::string UpdateManager::checkUpdate() {
    httplib::Client client("https://api.github.com");
    auto response = client.Get(("/repos"+ConfigManager::REPO_BASE_URL+"/releases/latest").c_str());
    nlohmann::json jsonBody = nlohmann::json::parse(response->body);
    return jsonBody["tag_name"];
}

void UpdateManager::doUpdate(std::string version) {

}