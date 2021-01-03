# SPDX-FileCopyrightText: 2020 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Quick Network NetworkAuth REQUIRED)

include_directories(.)

add_subdirectory(common)
add_subdirectory(net)
add_subdirectory(twitch)
add_subdirectory(ui)

add_executable(streamoverlord main.cpp qml.qrc)
enable_warnings_for(streamoverlord)

target_compile_definitions(streamoverlord
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(streamoverlord PRIVATE ui)
