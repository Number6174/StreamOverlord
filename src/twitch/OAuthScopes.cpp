// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "OAuthScopes.h"

QString Twitch::scopeName(Twitch::Scope s) {
    switch (s) {
        case Scope::analytics_read_extensions:
            return "analytics:read:extensions";
        case Scope::analytics_read_games:
            return "analytics:read:games";
        case Scope::bits_read:
            return "bits:read";
        case Scope::channel_edit_commercial:
            return "channel:edit:commercial";
        case Scope::channel_manage_broadcast:
            return "channel:manage:broadcast";
        case Scope::channel_manage_extensions:
            return "channel:manage:extensions";
        case Scope::channel_manage_redemptions:
            return "channel:manage:redemptions";
        case Scope::channel_read_hype_train:
            return "channel:read:hype_train";
        case Scope::channel_read_redemptions:
            return "channel:read:redemptions";
        case Scope::channel_read_stream_key:
            return "channel:read:stream_key";
        case Scope::channel_read_subscriptions:
            return "channel:read:subscriptions";
        case Scope::clips_edit:
            return "clips:edit";
        case Scope::moderation_read:
            return "moderation:read";
        case Scope::user_edit:
            return "user:edit";
        case Scope::user_edit_follows:
            return "user:edit:follows";
        case Scope::user_read_broadcast:
            return "user:read:broadcast";
        case Scope::user_read_email:
            return "user:read:email";
        case Scope::channel_moderate:
            return "channel:moderate";
        case Scope::chat_edit:
            return "chat:edit";
        case Scope::chat_read:
            return "chat:read";
        case Scope::whispers_read:
            return "whispers:read";
        case Scope::whispers_edit:
            return "whispers:edit";
    }
    Q_UNREACHABLE();
}

QString Twitch::scopeDescription(Twitch::Scope s) {
    switch (s) {
        case Scope::analytics_read_extensions:
            return "View analytics data for your extensions";
        case Scope::analytics_read_games:
            return "View analytics data for your games";
        case Scope::bits_read:
            return "View Bits information for your channel.";
        case Scope::channel_edit_commercial:
            return "Run commercials on a channel.";
        case Scope::channel_manage_broadcast:
            return "Manage your channel’s broadcast configuration, including updating channel configuration and managing stream markers and stream tags.";
        case Scope::channel_manage_extensions:
            return "Manage your channel’s extension configuration, including activating extensions.";
        case Scope::channel_manage_redemptions:
            return "Manage Channel Points custom rewards and their redemptions on a channel.";
        case Scope::channel_read_hype_train:
            return "Gets the most recent hype train on a channel.";
        case Scope::channel_read_redemptions:
            return "View Channel Points custom rewards and their redemptions on a channel.";
        case Scope::channel_read_stream_key:
            return "Read an authorized user’s stream key.";
        case Scope::channel_read_subscriptions:
            return "Get a list of all subscribers to your channel and check if a user is subscribed to your channel.";
        case Scope::clips_edit:
            return "Manage a clip object.";
        case Scope::moderation_read:
            return "View your channel’s moderation data including Moderators, Bans, Timeouts and Automod settings.";
        case Scope::user_edit:
            return "Manage a user object.";
        case Scope::user_edit_follows:
            return "Edit your follows.";
        case Scope::user_read_broadcast:
            return "View your broadcasting configuration, including extension configurations.";
        case Scope::user_read_email:
            return "Read an authorized user’s email address.";
        case Scope::channel_moderate:
            return "Perform moderation actions in a channel. The user requesting the scope must be a moderator in the channel.";
        case Scope::chat_edit:
            return "Send live stream chat and rooms messages.";
        case Scope::chat_read:
            return "View live stream chat and rooms messages.";
        case Scope::whispers_read:
            return "View your whisper messages.";
        case Scope::whispers_edit:
            return "Send whisper messages.";
    }
    Q_UNREACHABLE();
}
