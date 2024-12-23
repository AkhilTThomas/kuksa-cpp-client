add_executable(example example.cpp)
target_link_directories(example PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(example kuksa-cpp-client)
target_include_directories(example PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                 ${CMAKE_BINARY_DIR})
