// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_GITINFO_H
#define STREAMOVERLORD_GITINFO_H

// Note we are using an extern here to minimize the linking impact of a changing GIT
namespace Common {
    extern const char GIT_VERSION[];
}
#endif //STREAMOVERLORD_GITINFO_H
