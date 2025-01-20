cmake_minimum_required(VERSION 3.26.4)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-12")
project(GUI DESCRIPTION "gui lib" LANGUAGES CXX)
find_package(SDL2 REQUIRED)

find_package(SDL2_ttf REQUIRED)
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/Boton.cpp
    ${PROJECT_SOURCE_DIR}/ImageButton.cpp
    ${PROJECT_SOURCE_DIR}/callback.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../include)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2 )
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2_ttf )