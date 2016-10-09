# Core Controls

This repository contains utility libraries shared by both the primary and secondary controller software of the Formula Slug 2016 racecar, FS-0.

The style guide repository at https://github.com/wpilibsuite/styleguide contains our style guide for C and C++ code and formatting scripts.

## TODO
- Add node id to the constructor, and then use it when packaging the heartbeat message (and possibly others)
- Bring duplicate can stuf in primary and secondary controls into core controls (only what will be permanent, not the temporary testing portions)
- Add framework for showing beep codes via LED
  - Setting error code via enum class causes a specific blink pattern
