#include <raylib.h>
#include <string>


int main() {
    InitWindow(800, 600, "Top-Down Game");
    SetTargetFPS(60);



    struct Player{

    };

    struct Enemy{
        float speed =4.0f;
    };

    class Bullet{
        public:
        Vector2 pos;
        Vector2 speed;
    };

    Vector2 PlayerPos = {100, 100};
    Vector2 EnemyPos = {200,100};
    Vector2 BulletSpeed = 6;
    while (!WindowShouldClose()) {

        EnemyPos.x -= EnemyPos.x - PlayerPos.x;
        EnemyPos.y -= EnemyPos.y - PlayerPos.y;
        float r =  GetFrameTime();



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
        if (IsKeyDown(KEY_P)){

            DrawCircle(EnemyPos.x +10 , EnemyPos.y+10, 20, RED);
        }

        DrawText(std::to_string(r).c_str(), 50, 50, 20, RED);
        DrawRectangle(EnemyPos.x, EnemyPos.y, 20, 20, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
