# SPDX-FileCopyrightText: 2021 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

include(GetGitRevisionDescription)
git_describe_working_tree(GIT_VERSION "--tags")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/GitInfo.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/GitInfo.cpp @ONLY)
add_library(common
        ConfigManager.cpp ConfigManager.h
        Event.h Event.cpp
        NonceGenerator.cpp NonceGenerator.h
        Logging.cpp Logging.h
        VersionInfo.cpp VersionInfo.h
        ${CMAKE_CURRENT_BINARY_DIR}/GitInfo.cpp GitInfo.h)
enable_warnings_for(common)

target_link_libraries(common
        PRIVATE Qt${QT_VERSION_MAJOR}::Core
        spdlog::spdlog)