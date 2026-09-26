#include <raylib.h>

int main() {
    InitWindow(800, 600, "Top-Down Game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
