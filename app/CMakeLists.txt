add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARY_NAME} SDL imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_NAME} )
file(COPY ${CMAKE_SOURCE_DIR}/game/Assets/joystix-monospace.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Assets)