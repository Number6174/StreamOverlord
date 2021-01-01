<!--
SPDX-FileCopyrightText: 2020 Number6174

SPDX-License-Identifier: GPL-3.0-or-later
-->

# StreamOverlord

A standalone program to help manage interactivity for streamers. It is open source, free for general use, and does not take any portion of your tips or donations.

If you do use this program to make money for yourself, please consider supporting me to ensure the program will be maintained and improved. Direct donations or support on Patreon (forthcoming) are appreciated. Custom comissioned work may also be accepted depending on the project and availability.

Join the [Discord](https://discord.gg/MpN36Fnpf2) if you have any questions or need support.

# Current status
Prototype quality, not suitable for general use. 

[![REUSE status](https://api.reuse.software/badge/github.com/number6174/streamoverlord)](https://api.reuse.software/info/github.com/number6174/streamoverlord)


# Design Goals

Some of these are aspirational and may take a while before they are implemented. If one of them is particularly important to you, create a GitHub Issue requesting priority, or even consider commissioning custom work.

* Low resource usage
  * All reasonable attempts will be made to keep resource usage low
  * Add a later client to run on a game PC that just receives events from a streaming PC to dedicate as much of your resources to the game as possible
* Use an event/listener model
  * Provides stream interaction based upon viewer triggers
* Testability
  * Code thoroughly tested with extensive unit testing ensure quality
  * Allow configuration and testing of configuration with simulated events, allowing development of interations without needing to be live or waiting for specific events to occur
* Use a queue structure for events
  * Ordered synchronous queues. Events will be processed in order to completion before moving onto the next
  * Ordered asynchronous queues. Events will be processed as quickly as possible
* Multiple sources for events
  * [Twitch API](https://dev.twitch.tv/docs/api/) Events
  * Twitch Pubsub Events
  * Streamlabs Tips
  * StreamElements Tips
  * Others, including charity sources
* Detailed logging
  * Detailed log information stored for both analytic and debugging purposes
* Separate process from game or other streaming programs with restartability
  * In the unlikely event of a crash, allow StreamOverlord to be restarted with as minimal loss of data as possible
  * Being separate from other programs, game crashes, or network problems will have minimal impact on StreamOverlord
* Switch scenes in OBS/SLOBS
* Support templated output to easily create custom widgets displayable by OBS/SLOBS
  * Likely Mustache or Jinja formatted, subject to further research
  * This will allow for things like sub goals, donation goals, custom widgets
  * Can also modify game configurations
* Embedded V8 Javascript Engine used for customization
  * Provides full control for whatever you want to happen
  * A real programming language without weird custom syntax making it both easier to use existing programming tools, but also increase the pool of people who can help write customizations
* Various timers
  * General countdown timers
  * Extensible timers used for marathon type streams where events modify the time remaining
* Support for special events like Twitch's Hype Train
* Configuration via JSON
* Ability to interfere with controls
  * Potentially using [Interception](https://github.com/oblitum/Interception) or [capsicain](https://github.com/cajhin/capsicain)
  * Swap keyboard inputs, like reverse WASD
  * Block specific keystrokes, like can only strafe no forwards/backwards
  * Mouse drift, roughly like a worn out old control stick

# Developer Information

This project is laid out roughly in accordance to the [Pitchfork conventions](https://github.com/vector-of-bool/pitchfork)

Project dependencies:
* QT - Must be separately installed. Current 5.15.2, will move to 6.x once all used modules are available