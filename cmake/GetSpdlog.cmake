# SPDX-FileCopyrightText: 2021 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

# -*- cmake -*-

#[=======================================================================[.rst:
GetSpedlog
-------

Downloads and configures the spdlog library using the FetchContent CMake module.

This approach downloads spdlog from Github and a network connection may not always
be acceptable

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets:

``spdlog::spdlog``
  The spdlog library, if found

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``spdlog_POPULATED``
  True if spdlog has been downloaded and configured

#]=======================================================================]

include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.8.2
)

FetchContent_GetProperties(spdlog)
string(TOLOWER "spdlog" lcName)
if(NOT ${lcName}_POPULATED)
    FetchContent_Populate(spdlog)
    add_subdirectory(${${lcName}_SOURCE_DIR} ${${lcName}_BINARY_DIR})
endif()
