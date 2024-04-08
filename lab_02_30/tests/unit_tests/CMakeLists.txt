project(unitTests)

set(SOURCES test_triangle.cpp)

add_library(app SHARED ../app/ui/)
add_executable(unit_tests $(SOURCES))

target_link_libraries(unit_tests gtest gtest_main)
target_link_libraries(unit_tests app)
