# practiceday

## Top-down game (branch: `test-topdown-game`)

A simple top-down game written in C++20 with [raylib](https://www.raylib.com/) 6.0.

- **Move:** WASD or arrow keys
- **Goal:** collect yellow coins, avoid red enemies (a new enemy spawns every 5 coins)
- **Restart:** Enter

### Build & run

Requires CMake 3.24+ and a C++20 compiler. If raylib 6.0 is installed
(e.g. `brew install raylib`) it will be used; otherwise CMake downloads it automatically.

```sh
cmake -S . -B build
cmake --build build
./build/topdown_game
```
