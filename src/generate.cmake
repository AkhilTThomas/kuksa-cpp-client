# Recursively find all .proto files
file(GLOB_RECURSE proto_files "${CMAKE_SOURCE_DIR}/proto/*.proto")

add_library(proto-objects OBJECT ${PROTO_FILES})

target_link_libraries(proto-objects PUBLIC protobuf::libprotobuf gRPC::grpc++)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(PROTO_IMPORT_DIRS "${CMAKE_SOURCE_DIR}/proto")

# Ensure the output directory exists
file(MAKE_DIRECTORY ${PROTO_BINARY_DIR})

target_include_directories(proto-objects
                           PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

foreach(proto_file ${proto_files})
  # Generate protobuf code for each file
  protobuf_generate(
    TARGET
    proto-objects
    IMPORT_DIRS
    ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR
    "${PROTO_BINARY_DIR}/${PROTO_DIR}"
    PROTOS
    ${proto_file})

  # Generate gRPC services
  protobuf_generate(
    TARGET
    proto-objects
    LANGUAGE
    grpc
    GENERATE_EXTENSIONS
    .grpc.pb.h
    .grpc.pb.cc
    PLUGIN
    "protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    IMPORT_DIRS
    ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR
    "${PROTO_BINARY_DIR}/${PROTO_DIR}"
    PROTOS
    ${proto_file})
endforeach()
