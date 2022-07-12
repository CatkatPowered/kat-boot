//
// Created by CatMoe on 2022/7/11.
//

#include "modules/UpdateManager/UpdateManager.h"
#include "modules/CertManager/CertManager.h"
#include "modules/ConfigManager/ConfigManager.h"

#include <iostream>

int main() {
    UpdateManager::UpdateManagerInit();
    std::cout << "UpdateManager Init" << std::endl;
    CertManager::CertManagerInit();
    return 0;
}