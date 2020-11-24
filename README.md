# StreamOverlord

A standalone program to help manage interactivity for streamers. It is open source, free for general use, and does not take any portion of your tips or donations.

If you do use this program to make money for yourself, please consider supporting me to ensure the program will maintained and improved. Direct donations or support on Patreon (forthcoming) are appreciated.

# Current status
Prototype quality, not suitable for general use. 

# Future Design Goals

Some of these are aspirational and may take a while before they are implemented. If one of them is particularly important to you, create a GitHub Issue requesting priority, or even consider commissioning custom work.

* Use an event/listener model
  * Provides stream interaction based upon viewer triggers
* Testability
  * Code thoroughly tested with extensive unit testing ensure quality
  * Allow configuration and testing of configuration with simulated events, allowing development of interations without needing to be live or waiting for specific events to occur
* Use a queue structure for events
  * Ordered synchronous queues. Events will be processed in order to completion before moving onto the next
  * Ordered asynchronous queues. Events will be processed as quickly as possible
* Multiple sources for events
  * Twitch API Events
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