// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>

#include "common/ConfigManager.h"

#include <QJsonDocument>
#include <QJsonObject>

TEST(TokenJSONRead, Twitch) {
    QJsonObject obj;
    obj["twitch"] = "access-token";

    QJsonDocument jsonDocument;
    jsonDocument.setObject(obj);

    Common::TokenStorage ts;

    EXPECT_EQ(Common::processTokenJSON(jsonDocument, ts), Common::LoadTokenResult::Success);
    EXPECT_EQ(ts.twitchAccessToken, "access-token");
}

TEST(TokenJSONRead, NoEntries) {
    QJsonObject obj;

    QJsonDocument jsonDocument;
    jsonDocument.setObject(obj);

    Common::TokenStorage ts;

    EXPECT_EQ(Common::processTokenJSON(jsonDocument, ts), Common::LoadTokenResult::Success);
    EXPECT_EQ(ts.twitchAccessToken, "");
}