cmake_minimum_required(VERSION 3.5)

project(MazeSolver VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp

        # UI
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MazeSolver
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        # Maze
        maze/maze.h maze/maze.cpp
        maze/Cell.h maze/Cell.cpp
        maze/Wall.h
        maze/randomizedmaze.h maze/randomizedmaze.cpp
        maze/custommaze.h maze/custommaze.cpp
        maze/state.h
        maze/step.h maze/step.cpp
        maze/mazefilehandler.h maze/mazefilehandler.cpp

        # Algorithms
        algorithms/algorithm.h algorithms/algorithm.cpp

        # Path Finding Algorithms
        algorithms/solving/depthfirstsearch.h algorithms/solving/depthfirstsearch.cpp
        algorithms/solving/breadthfirstsearch.h algorithms/solving/breadthfirstsearch.cpp
        algorithms/solving/astarsearch.h algorithms/solving/astarsearch.cpp
        algorithms/solving/pathfindingalgorithm.h algorithms/solving/pathfindingalgorithm.cpp

        # Generating Algorithms
        algorithms/generating/generatingalgorithm.h algorithms/generating/generatingalgorithm.cpp
        algorithms/generating/randomizedprimsalgorithm.h algorithms/generating/randomizedprimsalgorithm.cpp

        # UI
        ui/customrectitem.h ui/customrectitem.cpp
    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MazeSolver APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MazeSolver SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MazeSolver
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(MazeSolver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/maze
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/solving
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/generating
)


target_link_libraries(MazeSolver PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MazeSolver)
endif()
set_target_properties(MazeSolver PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MazeSolver
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MazeSolver)
endif()
