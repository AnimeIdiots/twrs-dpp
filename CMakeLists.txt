cmake_minimum_required(VERSION 3.15)
project(TWRS-Bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(libs/DPP)
add_subdirectory(libs/toml11)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} dpp toml11)

target_include_directories(${PROJECT_NAME} PRIVATE libs/DPP/include libs/toml11)
