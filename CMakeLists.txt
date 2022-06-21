cmake_minimum_required(VERSION 3.15)

project(pid_simulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Charts REQUIRED)



set(HEADERS
    include/error_graph.h
    include/mainwindow.h
    include/mainwindow.ui
    include/pid_table_model.h
    include/simulator.h
    include/pid.h
)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/error_graph.cpp
    src/pid_table_model.cpp
    src/simulator.cpp
    src/pid.cpp
)

qt_add_executable(pid_simulator MANUAL_FINALIZATION ${HEADERS} ${SOURCES} )

target_link_libraries(pid_simulator PRIVATE Qt6::Widgets Qt6::Charts)

set_target_properties(pid_simulator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

qt_finalize_executable(pid_simulator)
