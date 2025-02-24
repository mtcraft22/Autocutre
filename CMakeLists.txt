cmake_minimum_required(VERSION 3.26.4)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-12")
project(Autocutre DESCRIPTION "cad app" LANGUAGES CXX)

add_subdirectory(src/GUI)
add_subdirectory(src/mtcad)
add_subdirectory(src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)