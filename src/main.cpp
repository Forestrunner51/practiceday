#include <raylib.h>


int main() {
    InitWindow(800, 600, "Top-Down Game");
    SetTargetFPS(60);

    Vector2 PlayerPos = {100, 100};
    Vector2 EnemyPos = {200,100};

    while (!WindowShouldClose()) {

        EnemyPos.x -= EnemyPos.x - PlayerPos.x;

        if (IsKeyDown(KEY_A)){
        PlayerPos.x -= 1;
        }
        if (IsKeyDown(KEY_D)){
        PlayerPos.x += 1;
        }
        if (IsKeyDown(KEY_W)){
        PlayerPos.y -= 1;
        }
        if (IsKeyDown(KEY_S)){
        PlayerPos.y += 1;
        }
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Hello, World!", 12, 12, 20, DARKBLUE);
        DrawCircle(PlayerPos.x, PlayerPos.y, 20, GREEN);

        DrawRectangle(EnemyPos.x, EnemyPos.y, 20, 20, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
