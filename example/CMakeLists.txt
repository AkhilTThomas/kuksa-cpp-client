set(EXAMPLES example_v1 example_v2)

foreach(EXAMPLE ${EXAMPLES})
  add_executable(${EXAMPLE} ${EXAMPLE}.cpp)

  target_link_libraries(${EXAMPLE} kuksaclient)
  target_link_directories(${EXAMPLE} PRIVATE ${CMAKE_BINARY_DIR})
  target_include_directories(${EXAMPLE} PUBLIC ${PROJECT_SOURCE_DIR}/include)

  set_target_properties(${EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                              ${CMAKE_BINARY_DIR}/bin)
endforeach()
