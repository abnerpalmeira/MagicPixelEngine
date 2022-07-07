cmake_minimum_required(VERSION 3.23.2)

project(MagicPixelEngine VERSION 0.0.1 LANGUAGES CXX)

if(NOT CMAKE_SIZEOF_VOID_P MATCHES 8)
	message(FATAL_ERROR "MagicPixelEngine supports only x64.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(APP_DIR "${CMAKE_CURRENT_LIST_DIR}/app")
set(CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(EXTERNAL_DIR "${CMAKE_CURRENT_LIST_DIR}/external")
# set(ENGINE_DIR "${CMAKE_CURRENT_LIST_DIR}/engine")

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
	set(OS_WINDOWS 1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
	set(OS_MACOSX 1)
endif()

add_subdirectory(${APP_DIR})
add_subdirectory(${EXTERNAL_DIR})


# add_executable(${PROJECT_NAME} app/main.cc)

# set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake")
# set(EXTERNAL_DIR "${CMAKE_CURRENT_LIST_DIR}/external")
# set(ENGINE_DIR "${CMAKE_CURRENT_LIST_DIR}/engine")

# add_subdirectory(${EXTERNAL_DIR})
# add_subdirectory(${ENGINE_DIR})