include("${CMAKE_DIR}/SDL.cmake")
include("${CMAKE_DIR}/SDL2_ttf.cmake")
set(IMGUI_SOURCES
    "imgui/imgui.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp"
    "imgui/backends/imgui_impl_sdl.cpp"
    "imgui/backends/imgui_impl_sdlrenderer.cpp")
set(IMGUI_HEADERS
    "imgui/imgui.h"
    "imgui/backends/imgui_impl_sdl.h"
    "imgui/backends/imgui_impl_sdlrenderer.h")
add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})
target_link_libraries(imgui PUBLIC SDL)
target_include_directories(imgui PUBLIC "imgui" )