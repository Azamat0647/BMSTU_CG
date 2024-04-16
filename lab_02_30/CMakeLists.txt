cmake_minimum_required(VERSION 3.5)

project(lab_02 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX)
    SET(CMAKE_INSTALL_RPATH lib)
endif()


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Charts REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Charts REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


if (CODE_CVRG)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/modules)

    include(CodeCoverage)
    append_coverage_compiler_flags()

endif()


enable_testing()

add_subdirectory(app)

#add_subdirectory(unit_tests)
