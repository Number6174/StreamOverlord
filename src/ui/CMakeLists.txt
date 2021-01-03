# SPDX-FileCopyrightText: 2021 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

add_library(ui
        Backend.h Backend.cpp
        EventModel.h EventModel.cpp
        QMLRegistrations.h QMLRegistrations.cpp
        MainGUI.h MainGUI.cpp
        )
enable_warnings_for(ui)

target_link_libraries(ui
        PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
target_link_libraries(ui
        PRIVATE common net twitch)