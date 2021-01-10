// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "QMLRegistrations.h"

#include "EventModel.h"
#include "ChangesModel.h"

void registerQML() {
    qmlRegisterType<EventModel>("StreamOverlord", 1, 0, "EventModel");
    qmlRegisterType<ChangesModel>("StreamOverlord", 1, 0, "ChangesModel");
}
