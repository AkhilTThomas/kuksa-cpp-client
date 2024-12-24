add_executable(example_v2 example_v2.cpp)
add_executable(example_v1 example_v1.cpp)

target_link_directories(example_v1 PRIVATE ${CMAKE_BINARY_DIR})
target_link_directories(example_v2 PRIVATE ${CMAKE_BINARY_DIR})

target_link_libraries(example_v1 kuksa-cpp-client)
target_link_libraries(example_v2 kuksa-cpp-client)

target_include_directories(example_v1 PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(example_v2 PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_target_properties(example_v1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                            ${CMAKE_BINARY_DIR}/bin)
set_target_properties(example_v2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                            ${CMAKE_BINARY_DIR}/bin)
