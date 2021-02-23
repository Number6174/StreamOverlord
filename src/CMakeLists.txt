# SPDX-FileCopyrightText: 2020 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



include_directories(.)

add_subdirectory(common)
add_subdirectory(net)
add_subdirectory(twitch)
add_subdirectory(ui)

add_executable(streamoverlord main.cpp dist.qrc qml.qrc)
enable_warnings_for(streamoverlord)

target_compile_definitions(streamoverlord
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(streamoverlord PRIVATE ui)
