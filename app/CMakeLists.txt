cmake_minimum_required(VERSION 3.5)
project(MagicPixelEngine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} MagicPixelEngine_engine)
target_include_directories(${PROJECT_NAME} PRIVATE MagicPixelEngine_engine)