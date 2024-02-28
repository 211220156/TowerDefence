cmake_minimum_required(VERSION 3.5)

project(TowerDenfence VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        map.cpp
        map.h
        place.h
        place.cpp
        res.qrc
        beginbutton.cpp
        beginbutton.h
        gamescene.cpp
        gamescene.h
        gameobject.cpp
        gameobject.h
        nut.cpp
        nut.h
        plant.cpp
        plant.h
        zombie.cpp
        zombie.h
        normalzombie.cpp
        normalzombie.h
        starfruit.cpp
        starfruit.h
        bullet.cpp
        bullet.h
        ballonzombie.cpp
        ballonzombie.h
        flagzombie.cpp
        flagzombie.h
        peashooter.cpp
        peashooter.h
        sunshine.cpp
        sunshine.h
        message.cpp
        message.h
        spikeweed.cpp
        spikeweed.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TowerDenfence
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TowerDenfence APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TowerDenfence SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TowerDenfence
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TowerDenfence PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(TowerDenfence PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TowerDenfence)
endif()

find_package(Qt5 COMPONENTS Core Gui Qml Quick MultimediaWidgets REQUIRED)
set(Qt5MultimediaWidgets_DIR D:/Qt/5.15.2/lib/cmake/Qt5MultimediaWidgets)#包的位置
target_link_libraries(TowerDenfence PRIVATE Qt5::Widgets Qt5::MultimediaWidgets)#链接到库

