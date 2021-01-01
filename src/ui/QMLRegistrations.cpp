// SPDX-FileCopyrightText: 2020 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "QMLRegistrations.h"

#include "EventModel.h"

// Ignore a MSVC warning inside the template
//#pragma warning(disable:4217)
void registerQML() {
    qmlRegisterType<EventModel>("StreamOverlord", 1, 0, "EventModel");
//#pragma warning(default:4217)
}
