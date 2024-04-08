project(tests LANGUAGES CXX)

find_package(GTest REQUIRED)

add_subdirectory(unit_tests)
