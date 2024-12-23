add_library(${PROJECT_NAME} kuksa_client.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog gRPC::grpc++
                      protobuf::libprotobuf proto-objects)
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                                                 ${CMAKE_BINARY_DIR})

include(generate.cmake)
