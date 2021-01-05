// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STREAMOVERLORD_OAUTHSCOPES_H
#define STREAMOVERLORD_OAUTHSCOPES_H

#include <QString>

namespace Twitch {
    enum class Scope {
        // From https://dev.twitch.tv/docs/authentication/#scopes
        // Twitch API
        analytics_read_extensions,
        analytics_read_games,
        bits_read,
        channel_edit_commercial,
        channel_manage_broadcast,
        channel_manage_extensions,
        channel_manage_redemptions,
        channel_read_hype_train,
        channel_read_redemptions,
        channel_read_stream_key,
        channel_read_subscriptions,
        clips_edit,
        moderation_read,
        user_edit,
        user_edit_follows,
        user_read_broadcast,
        user_read_email,
        // Chat and PubSub
        channel_moderate,
        chat_edit,
        chat_read,
        whispers_read,
        whispers_edit
    };

    QString scopeName(Scope s);
    QString scopeDescription(Scope s);
}


#endif //STREAMOVERLORD_OAUTHSCOPES_H
