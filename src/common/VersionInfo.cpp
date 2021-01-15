// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "VersionInfo.h"

#include "GitInfo.h"

QString Common::getCurrentVersion() {
    return QString(GIT_VERSION);
}
