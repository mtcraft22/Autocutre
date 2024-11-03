cmake_minimum_required(VERSION 3.26.4)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-12")
project(mtcad DESCRIPTION "shapes lib " LANGUAGES CXX)
find_package(SDL2 REQUIRED)
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/Rectangle.cpp
    ${PROJECT_SOURCE_DIR}/Triangle.cpp
    ${PROJECT_SOURCE_DIR}/curve.cpp
    ${PROJECT_SOURCE_DIR}/circle.cpp
    ${PROJECT_SOURCE_DIR}/Node.cpp
    ${PROJECT_SOURCE_DIR}/line.cpp
    ${PROJECT_SOURCE_DIR}/ellipse.cpp
    ${PROJECT_SOURCE_DIR}/quadratic_curve.cpp

)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../include)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2 )