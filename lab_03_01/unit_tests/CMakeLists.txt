
find_package(GTest REQUIRED)

set(TESTS_SOURCES 
    
    )

add_executable(unit_tests ${TESTS_SOURCES})

target_link_libraries(unit_tests app_lib gtest gtest_main Qt${QT_VERSION_MAJOR}::Core)

include(GoogleTest)
gtest_discover_tests(unit_tests)
