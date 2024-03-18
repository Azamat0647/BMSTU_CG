project(lab_01 LANGUAGES CXX)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (test)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/modules)

    include(CodeCoverage)
    append_coverage_compiler_flags()

    enable_testing()

    add_subdirectory(tests)
endif()

add_subdirectory(app)
