cmake_minimum_required(VERSION 3.16)

project(demo_github_workflow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(config_loader src/config_loader.cpp)
target_include_directories(config_loader PRIVATE src)

add_executable(string_utils src/string_utils.cpp)
add_executable(user_manager src/user_manager.cpp)
