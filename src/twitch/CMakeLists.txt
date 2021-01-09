# SPDX-FileCopyrightText: 2021 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

add_library(twitch
        TokenManager.h TokenManager.cpp
        OAuthScopes.cpp OAuthScopes.h)
enable_warnings_for(twitch)

# Note: This is intentionally not private because this library is just a
# mini static one for use in this project only
target_link_libraries(twitch PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::NetworkAuth
        common
        spdlog::spdlog)

#target_link_libraries(twitch PRIVATE
#        common
#        spdlog::spdlog)