cmake_minimum_required(VERSION 3.10)

project(ip_filter VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Application

add_executable(ip_filter src/ip-filter.cpp)

target_include_directories(ip_filter PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Tests

enable_testing()

add_executable(ip_filter_tests tests/test_filter_ip.cpp)

target_include_directories(ip_filter_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_test(NAME ip_filter_tests COMMAND ip_filter_tests)

# Installation

install(TARGETS ip_filter RUNTIME DESTINATION bin)

# Packaging (CPack)

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "ip-filter")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "otus")

include(CPack)
