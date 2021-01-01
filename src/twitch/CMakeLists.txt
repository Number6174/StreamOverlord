# SPDX-FileCopyrightText: 2021 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

add_library(twitch
        TwitchSSO.h TwitchSSO.cpp
        )
enable_warnings_for(twitch)

target_link_libraries(twitch
        PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::NetworkAuth)