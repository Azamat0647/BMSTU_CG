
set(SOURCE_DIR src)
set(UI_DIR ui)
set(MODEL_DIR model)

set(PROJECT_SOURCES
        ${SOURCE_DIR}/${UI_DIR}/mainwindow.cpp
        ${SOURCE_DIR}/${UI_DIR}/mainwindow.h
        ${SOURCE_DIR}/${UI_DIR}/itemdelegate.cpp
        ${SOURCE_DIR}/${UI_DIR}/itemdelegate.h
        ${SOURCE_DIR}/${UI_DIR}/canvas.cpp
        ${SOURCE_DIR}/${UI_DIR}/canvas.h
        ${SOURCE_DIR}/${UI_DIR}/mainwindow.ui
        ${SOURCE_DIR}/${MODEL_DIR}/triangle.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/triangle.h
        ${SOURCE_DIR}/${MODEL_DIR}/setofpoints.cpp
        ${SOURCE_DIR}/${MODEL_DIR}/setofpoints.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_library(app_lib SHARED
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_add_executable(app
        MANUAL_FINALIZATION
        ${SOURCE_DIR}/main.cpp
#        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET lab_01 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(app SHARED
            ${SOURCE_DIR}/main.cpp
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_library(app_lib SHARED ${PROJECT_SOURCES})
        add_executable(app ${SOURCE_DIR}/main.cpp ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(app_lib PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(app PRIVATE app_lib)


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

install(TARGETS app app_lib DESTINATION . CONFIGURATIONS Release)
