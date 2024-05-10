
find_package(GTest REQUIRED)

add_executable(cli main.cpp)

target_link_libraries(cli app_lib Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)


