include(ExternalProject)

set(SDL2_TTF_VERSION "2.0.18")
set(SDL2_TTF_VERSION_STRING "SDL2_ttf-${SDL2_TTF_VERSION}")

set(SDL2_TTF_ROOT_DIR "${EXTERNAL_DIR}/${SDL2_TTF_VERSION_STRING}")
set(SDL2_TTF_MSVC_DIR "${SDL2_TTF_ROOT_DIR}/VisualC")

if(OS_WINDOWS)
	set(CONFIGURE_COMMAND "")
	set(BUILD_COMMAND
		MSBuild
			"${SDL2_TTF_MSVC_DIR}/SDL2_ttf.sln"
			/p:PlatformToolset=v142 # Default: v100
			/p:Configuration=${CMAKE_BUILD_TYPE}
			/p:Platform=x64
			/m)
	set(BUILD_BYPRODUCTS
		"${SDL2_TTF_MSVC_DIR}/x64/${CMAKE_BUILD_TYPE}/SDL2_ttf.lib")

	install(
		FILES "${SDL2_TTF_MSVC_DIR}/x64/${CMAKE_BUILD_TYPE}/SDL2_ttf.dll"
		DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()

if(OS_MACOSX)
	find_package(SDL2_ttf REQUIRED)
	add_library(SDL2_TTF INTERFACE)
	target_include_directories(SDL2_TTF INTERFACE ${SDL2_TTF_INCLUDE_DIRS})
	target_link_libraries(SDL2_TTF INTERFACE ${SDL2_TTF_LIBRARIES})
	return()
endif()

ExternalProject_Add(
	SDL2_TTFExternal
	PREFIX ${SDL2_TTF_VERSION_STRING}

	DOWNLOAD_DIR ${EXTERN_DIR}
	URL "https://www.libsdl.org/projects/SDL_ttf/release/${SDL2_TTF_VERSION_STRING}.tar.gz"

	SOURCE_DIR ${SDL2_TTF_ROOT_DIR}
	BINARY_DIR ${SDL2_TTF_ROOT_DIR}

	CONFIGURE_COMMAND "${CONFIGURE_COMMAND}"
	BUILD_COMMAND "${BUILD_COMMAND}"
	INSTALL_COMMAND ""

	BUILD_BYPRODUCTS ${BUILD_BYPRODUCTS}
)

add_library(SDL2_TTF INTERFACE)
add_dependencies(SDL2_TTF SDL2_TTFExternal)
target_include_directories(SDL2_TTF INTERFACE "${SDL2_TTF_ROOT_DIR}")
target_link_libraries(SDL2_TTF INTERFACE ${BUILD_BYPRODUCTS})
