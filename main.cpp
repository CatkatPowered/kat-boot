//
// Created by CatMoe on 2022/7/11.
//

#include "modules/UpdateManager/UpdateManager.h"
#include "modules/CertManager/CertManager.h"

int main() {
    UpdateManager::UpdateManagerInit();
    CertManager::CertManagerInit();
    return 0;
}