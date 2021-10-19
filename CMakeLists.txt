cmake_minimum_required(VERSION 3.5)
project(zn_gestion VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_subdirectory(./libs/)
set(PROJECT_SOURCES
       ./src/main.c
)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(nono ${PROJECT_SOURCES})

target_link_libraries(nono PRIVATE Qt${QT_VERSION_MAJOR}::Widgets mnlibrary cqt)

set_target_properties(nono PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)



