# Gluttony Yuyuko

A simple 2D snake-style game developed with C++ and SFML.

This project was originally created as a small C++ practice project.  
It uses SFML for graphics, window handling, keyboard input, and audio playback.

## Features

- 2D snake-style gameplay
- Character movement and collision detection
- Food generation and score-related logic
- Image and audio resource loading
- Keyboard event handling
- Object-oriented structure with multiple classes
- Built and debugged with Visual Studio 2022

## Technologies

- C++
- SFML 2.6.0
- Visual Studio 2022
- Windows x64

## Project Structure

```text
Gluttony-Yuyuko/
├── 貪吃幽幽子.sln
├── 貪吃幽幽子/
│   ├── main.cpp
│   ├── game_class.cpp / game_class.h
│   ├── food_class.cpp / food_class.h
│   ├── sound_class.cpp / sound_class.h
│   ├── Saigyouji_Yuyuko_Fomo_class.cpp / .h
│   ├── images/
│   ├── music/
│   └── SFML-2.6.0/
```

## How to Build

1. Open `貪吃幽幽子.sln` with Visual Studio 2022.
2. Set the build configuration to `Debug | x64`.
3. Make sure the SFML include path is set:

```text
$(ProjectDir)SFML-2.6.0\include
```

4. Make sure the SFML library path is set:

```text
$(ProjectDir)SFML-2.6.0\lib
```

5. For Debug mode, link the following libraries:

```text
sfml-graphics-d.lib
sfml-window-d.lib
sfml-system-d.lib
sfml-audio-d.lib
sfml-network-d.lib
```

6. Press `F5` or click `Local Windows Debugger` to run the game.

## What I Practiced

Through this project, I practiced:

- C++ class design
- Splitting code into header and source files
- Using a third-party C++ library
- Handling game loops and keyboard input
- Managing image and audio resources
- Building and debugging a C++ project in Visual Studio

## Notes

This is a personal practice project and not a commercial game.

Some assets may need to be replaced before using this project as a public portfolio project.
