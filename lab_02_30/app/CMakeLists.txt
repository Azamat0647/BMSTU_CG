
set(SOURCE_DIR src)
set(UI_DIR ui)
set(MODEL_DIR model)

set(PROJECT_SOURCES
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/${UI_DIR}/mainwindow.cpp
        ${SOURCE_DIR}/${UI_DIR}/canvas.h
        ${SOURCE_DIR}/${UI_DIR}/canvas.cpp
        ${SOURCE_DIR}/${UI_DIR}/mainwindow.h
        ${SOURCE_DIR}/${UI_DIR}/mainwindow.ui
        ${SOURCE_DIR}/${MODEL_DIR}/figure.h
        ${SOURCE_DIR}/${MODEL_DIR}/shape.h
        ${SOURCE_DIR}/${MODEL_DIR}/shape.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/object2d.h
        ${SOURCE_DIR}/${MODEL_DIR}/drawer.h
        ${SOURCE_DIR}/${MODEL_DIR}/drawer.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/figure.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/ellipse.h
        ${SOURCE_DIR}/${MODEL_DIR}/ellipse.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/cross.h
        ${SOURCE_DIR}/${MODEL_DIR}/cross.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/rhombus.h
        ${SOURCE_DIR}/${MODEL_DIR}/rhombus.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/rectangle.h
        ${SOURCE_DIR}/${MODEL_DIR}/rectangle.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/point2d.h
        ${SOURCE_DIR}/${MODEL_DIR}/point2d.cpp
)

include_directories(src/model, src/ui)

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
