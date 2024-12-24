include(GNUInstallDirs)
set(INCLUDE_INSTALL_DIR
    ${CMAKE_INSTALL_INCLUDEDIR}/kuksaclient
    CACHE PATH "Location of header files")

set(SYSCONFIG_INSTALL_DIR
    ${CMAKE_INSTALL_SYSCONFDIR}/kuksaclient
    CACHE PATH "Location of configuration files")

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/kuksaclientConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/kuksaclientConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kuksaclient
  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/kuksaclientConfigVersion.cmake
  VERSION 0.0.1
  COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kuksaclientConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/kuksaclientConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kuksaclient)