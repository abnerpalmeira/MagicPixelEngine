include(ExternalProject)

set(SDL2_TTF_VERSION "2.0.13")
set(SDL2_TTF_VERSION_STRING "SDL2_ttf-${SDL2_TTF_VERSION}")

set(SDL2_TTF_ROOT_DIR "${EXTERNAL_DIR}/${SDL2_TTF_VERSION_STRING}")
set(SDL2_TTF_MSVC_DIR "${SDL2_TTF_ROOT_DIR}/VisualC")

# if(OS_WINDOWS)
# 	set(CONFIGURE_COMMAND "")
# 	set(BUILD_COMMAND
# 		MSBuild
# 			"${SDL2_TTF_MSVC_DIR}/SDL2_TTF.sln"
# 			/p:PlatformToolset=v142 # Default: v100
# 			/p:Configuration=${CMAKE_BUILD_TYPE}
# 			/p:Platform=x64
# 			/m)
# 	set(BUILD_BYPRODUCTS
# 		"${SDL2_TTF_MSVC_DIR}/x64/${CMAKE_BUILD_TYPE}/SDL2_TTF2.lib"
# 		"${SDL2_TTF_MSVC_DIR}/x64/${CMAKE_BUILD_TYPE}/SDL2_TTF2main.lib")

# 	install(
# 		FILES "${SDL2_TTF_MSVC_DIR}/x64/${CMAKE_BUILD_TYPE}/SDL2_TTF2.dll"
# 		DESTINATION "${CMAKE_INSTALL_PREFIX}")
# endif()

if(OS_MACOSX)
	set(CONFIGURE_COMMAND ./configure)
	set(BUILD_COMMAND make
		COMMAND install_name_tool
			-id
			"@executable_path/../Frameworks/libSDL2_ttf-2.0.0.dylib"
			"${SDL2_TTF_ROOT_DIR}/.libs/libSDL2_ttf-2.0.0.dylib")
	set(BUILD_BYPRODUCTS
		"${SDL2_TTF_ROOT_DIR}/.libs/libSDL2_ttf-2.0.0.dylib")

	install(
		FILES "${SDL2_TTF_ROOT_DIR}/.libs/libSDL2_ttf-2.0.0.dylib"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/MagicPixelEngine.app/Contents/Frameworks")
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
