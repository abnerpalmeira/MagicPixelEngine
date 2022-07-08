set(LIBRARY_SOURCES
     "editor/widgets/hierarchy.cc"
     "editor/widgets/inspector.cc"
     "editor/widgets/viewer.cc"
     "core/engine.cc")
set(LIBRARY_HEADERS
     "editor/widgets/hierarchy.h"
     "editor/widgets/inspector.h"
     "editor/widgets/viewer.h"
     "core/engine.h")

add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS})
target_link_libraries(${LIBRARY_NAME} PUBLIC SDL imgui)
target_include_directories(${LIBRARY_NAME} PUBLIC ${ENGINE_DIR})