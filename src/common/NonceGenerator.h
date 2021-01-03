// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_NONCEGENERATOR_H
#define STREAMOVERLORD_NONCEGENERATOR_H

#include <string>

namespace common {
    [[nodiscard]] std::string generateOAuthState(int length = 20);
}
#endif //STREAMOVERLORD_NONCEGENERATOR_H
