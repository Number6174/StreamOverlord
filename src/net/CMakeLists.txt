# SPDX-FileCopyrightText: 2021 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

add_library(net
        NetworkManager.h NetworkManager.cpp
        OAuthHTTPServer.cpp OAuthHTTPServer.h)
enable_warnings_for(net)

# Note: This is intentionally not private because this library is just a
# mini static one for use in this project only
target_link_libraries(net PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Network)
