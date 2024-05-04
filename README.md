# GOL

The mythical Conway's Game of Life made in C using raylib.

# Preview

[Preview](https://github.com/SrVariable/GOL/tree/master/preview/video.webm)

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
