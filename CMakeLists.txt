cmake_minimum_required(VERSION 3.22)
project(kat-boot)

set(CMAKE_C_STANDARD 23)

add_executable(kat-boot main.cpp modules/UpdateManager/UpdateManager.cpp modules/UpdateManager/UpdateManager.h)
