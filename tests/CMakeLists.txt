set(Boost_NO_BOOST_CMAKE ON)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(ip_filter_tests test_filter_ip.cpp)

target_include_directories(ip_filter_tests PRIVATE ${PROJECT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})

target_link_libraries(ip_filter_tests PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME ip_filter_tests COMMAND ip_filter_tests)

