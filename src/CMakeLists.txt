cmake_minimum_required(VERSION 3.26.4)
project(Autocutre DESCRIPTION "cad app" LANGUAGES CXX)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/main.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../include)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2 )
target_link_libraries(${PROJECT_NAME} PUBLIC GUI )
target_link_libraries(${PROJECT_NAME} PUBLIC mtcad )
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2_image )