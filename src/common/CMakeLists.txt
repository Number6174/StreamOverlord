# SPDX-FileCopyrightText: 2021 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

add_library(common
        Event.h Event.cpp
        NonceGenerator.cpp NonceGenerator.h)
enable_warnings_for(common)

target_link_libraries(common
        PRIVATE Qt${QT_VERSION_MAJOR}::Core)