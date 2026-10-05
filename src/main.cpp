#include <raylib.h>
#include <string>
#include <cmath>

int main() {
    InitWindow(800, 600, "Top-Down Game");
    SetTargetFPS(60);


    Vector2 PlayerPos = {100, 100};
    float TX = 500;
    float TY = 500;
    float GRX = 50;
    float GRY = 50;
    Vector2 EnemyPos = {TX,TY};
    Vector2 GridPos = {GRX, GRY};
    Vector2 BulletSpeed = {6,3};
    float num = 30;

    while (!WindowShouldClose()) {


        TX  = EnemyPos.x - PlayerPos.x;
        TY  = EnemyPos.y - PlayerPos.y;
        double num = std::sqrt(TX*TX + TY*TY);

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

        for (int i =0; i<num; i++){

            if (i  < 10  && i != 18 && i != 28 && i != 38 && i != 48 ){
            DrawCircle(GridPos.x + i * 10, GridPos.y , 20, BLUE);
}
            else if (i < 20){
                DrawCircle(GridPos.x + i * 40, GridPos.y + i * 5, 20, PURPLE);
            }

            else if (i < 30){
                DrawCircle(GridPos.x + i * 40, GridPos.y + i * 5, 20, YELLOW);
            }

            else if (i < 40){
                DrawCircle(GridPos.x + i * 40, GridPos.y + i * 5, 20, ORANGE);

        }
        }


        DrawText(std::to_string(TX).c_str(), 300, 50, 20, RED);
        DrawText(std::to_string(TY).c_str(), 300, 300, 20, RED);
        DrawText(std::to_string(r).c_str(), 50, 50, 20, RED);

        DrawRectangle(EnemyPos.x, EnemyPos.y, 20, 20, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
