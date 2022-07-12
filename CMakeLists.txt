cmake_minimum_required(VERSION 3.22)
project(kat-boot)

set(CMAKE_CXX_STANDARD 23)

# 设置CMake所需要的包
find_package(LLVM REQUIRED CONFIG)
find_package(OpenSSL REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "OpenSSL Version: ${OPENSSL_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})


add_executable(
        kat-boot main.cpp
        modules/ConfigManager/ConfigManager.cpp
        modules/UpdateManager/UpdateManager.cpp
        modules/Utils/toml.h modules/CertManager/CertManager.cpp modules/CertManager/CertManager.h)

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(kat-boot ${llvm_libs})
target_link_libraries(kat-boot OpenSSL::SSL)
