# GOL

The mythical Conway's Game of Life made in C using raylib.

# Preview

https://github.com/SrVariable/GOL/assets/96599624/68378f84-1505-4b04-8f26-13d9cb6189b5

# Installation

## Debian / Ubuntu

```shell
sudo apt update && sudo apt install build-essential git \
libasound2-dev libx11-dev libxrandr-dev libxi-dev \
libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev \
libxinerama-dev libwayland-dev libxkbcommon-dev
```

# Controls

|Key|Description|
|-|-|
|<kbd>Space</kbd>|Pause/Play game|
|<kbd>B</kbd>|Blinker|
|<kbd>G</kbd>|Glider|
|<kbd>Left Click</kbd>|Put cell|
|<kbd>.</kbd>|Increase speed|
|<kbd>,</kbd>|Decrease speed|

# How to play

Execute ```make run``` and it will start the game. Left click on a dead cell to put an alive cell or viceversa.
To put a pattern, hold its respective key and left click. For example <kbd>G</kbd> + <kbd>Left Click</kbd> will place
a Glider in the selected zone.

# References

- Game of Life: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
- Patterns: https://www.researchgate.net/figure/Selected-morphologies-in-the-Game-of-Life-Their-identification-in-the-environment_fig5_318515088
- Raylib: https://github.com/raysan5/raylib/blob/master/src/raylib.h
