add_executable(ip_filter ip-filter.cpp)

target_include_directories(ip_filter PRIVATE ${PROJECT_SOURCE_DIR}/include)

install(TARGETS ip_filter RUNTIME DESTINATION bin)
