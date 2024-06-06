# GOL

The mythical Conway's Game of Life made in C using [raylib](https://github.com/raysan5/raylib).

# Preview

[preview.webm](https://github.com/SrVariable/GOL/assets/96599624/5661c44a-a311-429a-9292-a2223cad5a9f)

# Installation

## Debian / Ubuntu

```shell
sudo apt update && sudo apt install build-essential git \
libasound2-dev libx11-dev libxrandr-dev libxi-dev \
libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev \
libxinerama-dev libwayland-dev libxkbcommon-dev
```

## Windows

Follow steps 1, 2, 3: https://github.com/raysan5/raylib/wiki/Working-on-Windows#manual-setup-with-w64devkit

# Controls

|Key|Description|
|-|-|
|<kbd>Space</kbd>|Pause / Play game|
|<kbd>B</kbd>|Blinker|
|<kbd>G</kbd>|Glider / Gospel Gun Glider|
|<kbd>Left Click</kbd>|Put cell|
|<kbd>Right Click</kbd>|Remove cell|
|<kbd>.</kbd>|Increase speed|
|<kbd>,</kbd>|Decrease speed|

# How to play

Execute ```make run``` and it will start the game. Left click on a dead cell to put an alive cell or viceversa.
To put a pattern, hold its respective key and left click. For example <kbd>G</kbd> <kbd>Left Click</kbd> will place
a Glider in the selected zone.

# References

- Game of Life: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
- Patterns: https://www.researchgate.net/figure/Selected-morphologies-in-the-Game-of-Life-Their-identification-in-the-environment_fig5_318515088
- Gospel Gun Glider: https://conwaylife.com/patterns/gosperglidergun.cells
- Raylib: https://github.com/raysan5/raylib/blob/master/src/raylib.h

# Contributing

If you find any bug or have any suggestion, please open an issue [here](https://github.com/SrVariable/BFL/issues/new).
