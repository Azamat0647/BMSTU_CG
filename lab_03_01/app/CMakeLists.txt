
set(SOURCE_DIR src)
set(UI_DIR ui)
set(MODEL_DIR model)

set(PROJECT_SOURCES
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/${UI_DIR}/mainwindow.cpp
        ${SOURCE_DIR}/${UI_DIR}/mainwindow.h
        ${SOURCE_DIR}/${UI_DIR}/mainwindow.ui
        ${SOURCE_DIR}/${MODEL_DIR}/drawer.h
        ${SOURCE_DIR}/${MODEL_DIR}/drawer.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/controller.h
        ${SOURCE_DIR}/${MODEL_DIR}/controller.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/drawlinealgorithms.h
        ${SOURCE_DIR}/${MODEL_DIR}/algorithms/bresenham.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/algorithms/wu.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/algorithms/dda.cpp
)

include_directories(${SOURCE_DIR}/${MODEL_DIR}, ${SOURCE_DIR}/${UI_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET lab_01 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(app SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(app ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)


set_target_properties(app PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(app)
endif()

install(TARGETS app DESTINATION . CONFIGURATIONS Release)
