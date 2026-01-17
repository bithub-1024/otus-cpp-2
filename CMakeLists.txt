cmake_minimum_required(VERSION 3.10)

project(ip_filter VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

install(TARGETS ip_filter DESTINATION bin)

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "ip-filter")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "otus")

include(CPack)

add_executable(ip_filter src/ip-filter.cpp)
