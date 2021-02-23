# SPDX-FileCopyrightText: 2020 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

set(TEST_LINK_COMPONENTS
        common
        Qt${QT_VERSION_MAJOR}::Core
        spdlog::spdlog)

add_unittest(commonTests
        ConfigManager.cpp)