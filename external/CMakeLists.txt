include("${CMAKE_DIR}/SDL.cmake")
include("${CMAKE_DIR}/SDL2_ttf.cmake")
set(IMGUI_SOURCES
    "imgui/imgui.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp"
    "imgui/backends/imgui_impl_sdl2.cpp"
    "imgui/backends/imgui_impl_sdlrenderer2.cpp")
set(IMGUI_HEADERS
    "imgui/imgui.h"
    "imgui/backends/imgui_impl_sdl2.h"
    "imgui/backends/imgui_impl_sdlrenderer2.h")
add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})
target_link_libraries(imgui PUBLIC SDL)
target_include_directories(imgui PUBLIC "imgui" )