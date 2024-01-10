cmake_minimum_required(VERSION 3.5)

project(C201Pr VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

set(PROJECT_SOURCES
        src/main.cpp
        src/gamemenu.cpp
        src/gamemenu.h
        src/gamemenu.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(C201Pr
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

               src/unit.h src/unit.cpp
               src/user.h src/user.cpp
               src/player.h src/player.cpp
               src/ai.h src/ai.cpp
               src/map.h src/map.cpp
               src/infantry.h src/infantry.cpp
               src/cavalry.h src/cavalry.cpp
               src/artillery.h src/artillery.cpp
               src/scenario.h src/scenario.cpp
               src/obstacle.h src/obstacle.cpp
               src/river.cpp src/river.h
               src/swamp.h src/swamp.cpp
               resources.qrc

               src/game.h src/game.cpp src/game.ui
               src/settings.h src/settings.cpp
               src/commander.h
               src/commander.cpp
               README.md





    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET C201Pr APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(C201Pr SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(C201Pr
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(C201Pr PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(C201Pr PRIVATE Qt6::Multimedia)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.C201Pr)
endif()
set_target_properties(C201Pr PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS C201Pr
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(C201Pr)
endif()
