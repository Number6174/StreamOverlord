# SPDX-FileCopyrightText: 2020 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.17)
project(streamoverlord LANGUAGES CXX)

# Add path for custom modules
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
        )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CompilerSetup)
colorize_output()

# External libraries
include(GetSpdlog)
include(GetGoogletest)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Quick Network NetworkAuth REQUIRED)

# Project directories
add_subdirectory(src)
add_subdirectory(tests)
