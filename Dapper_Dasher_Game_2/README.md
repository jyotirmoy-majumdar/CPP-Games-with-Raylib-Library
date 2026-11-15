# Dapper Dasher – Game 2

**Dapper Dasher** is a 2D side-scrolling platform game that I developed using C++ and Raylib as part of my game development learning journey.

In this game, I control Scarfy, jump over incoming nebula obstacles, and try to avoid collisions. The game features animated sprites, scrolling backgrounds, a parallax effect and collision detection.

## Technologies Used

- C++
- Raylib
- Makefile
- Visual Studio Code

## Raylib Functions and Features Used

- `InitWindow()` and `CloseWindow()` – Window management.
- `BeginDrawing()` and `EndDrawing()` – Rendering loop.
- `LoadTexture()` and `UnloadTexture()` – Texture resource management.
- `DrawTextureEx()` – Drawing and scaling textures.
- `LoadFont()` and `UnloadFont()` – Custom font management.
- `DrawTextEx()` and `MeasureTextEx()` – Rendering and positioning text.
- `GetFrameTime()` – Delta time for frame-independent movement.
- `IsKeyPressed()` – Keyboard input.
- `CheckCollisionRecs()` – Rectangle-based collision detection.

## Techniques and Concepts Implemented

- **Player Movement and Jumping:** Implemented gravity, vertical velocity and jumping mechanics.
- **Delta Time:** Used frame time to make movement independent of frame rate.
- **Sprite Sheet Animation:** Animated Scarfy and nebula obstacles using source rectangles, frame indexing and animation timers.
- **Structures and Arrays:** Used an `AnimData` structure to organize animation information and an array to manage multiple obstacles.
- **Reusable Functions:** Separated animation updates, background scrolling and text positioning into reusable functions.
- **Pass-by-Value and Pass-by-Reference:** Practised passing structures and variables to functions and understanding how modifications affect original data.
- **Parallax Scrolling:** Created three scrolling background layers with different speeds to simulate depth.
- **Collision Detection:** Implemented rectangular hitboxes using `CheckCollisionRecs()` and adjusted collision boundaries with padding.
- **Custom Fonts:** Integrated Pixelify Sans and calculated text positions to center messages on the screen.

## Mathematics Used

- 2D screen coordinates and positions.
- Velocity, gravity and delta-time movement.
- Sprite sheet indexing using row, column and frame dimensions.
- Background scrolling distance: `speed × deltaTime`.
- Text centering using measured width and height.
- Rectangle overlap and collision detection.

## What I Learned

While developing this game, I improved my understanding of Raylib, game loops, animation systems, basic physics, collision detection and game object management.

I also gained practical experience with C++ structures, arrays, functions, references and resource management while building an actual playable game.

## Author

**Developed by:** Jyotirmoy Majumdar

**Language:** C++

**Library:** Raylib
