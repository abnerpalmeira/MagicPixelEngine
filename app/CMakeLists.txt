add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARY_NAME} SDL imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_NAME} )