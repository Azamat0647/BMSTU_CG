project(tests LANGUAGES CXX)

find_package(GTest REQUIRED)

set(UNIT_TESTS_DIR unit_tests)

add_executable(tests main.cpp)
target_link_libraries(tests GTest::gtest)