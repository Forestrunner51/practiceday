#include <raylib.h>
#include <iostream>
#include <string>
#include <list>
#include <cmath>

int main() {
    InitWindow(800, 600, "Top-Down Game");
    SetTargetFPS(60);

    std::list<std::string> cars = {"Volvo", "BMW","Ford", "Mazda"};
    std::list<std::string> track = {"Volvo", "BMW","Ford", "Mazda"};

    Vector2 PlayerPos = {100, 100};
    float TX = 500;
    float TY = 500;
    float GRX = 50;
    float GRY = 50;
    Vector2 EnemyPos = {TX,TY};
    Vector2 GridPos = {GRX, GRY};
    Vector2 BulletSpeed = {6,3};
    Vector2 mousePos = {0,0};
    float num = 10;

    while (!WindowShouldClose()) {


        TX  = EnemyPos.x - PlayerPos.x;
        TY  = EnemyPos.y - PlayerPos.y;
        double num2 = std::sqrt(TX*TX + TY*TY);

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

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            DrawText("Mouse Clicked!", 20, 60, 20, DARKBLUE);
            mousePos = GetMousePosition();
            DrawText(std::to_string(mousePos.x).c_str(), 20, 450, 20, WHITE);
            DrawText(std::to_string(mousePos.y).c_str(), 20, 500, 20, WHITE);

        }
        if (mousePos.x < 430 && mousePos.y < 430){

            track.push_back("Hit");
                DrawText("Hit!", mousePos.x, mousePos.y, 20, YELLOW);


            }

        for (int i =0; i<num; i++){

            for (int j = 0; j < num; j++){

                DrawCircle(GridPos.x + i * 40, GridPos.y + j * 40, 20, BLUE);
                DrawText(std::to_string(i).c_str(), GridPos.x + i * 40, GridPos.y + j * 40, 20, RED);
            }
        }

        DrawText(cars.front().c_str(), 500,450,20,GREEN);
         std::cout << cars.front();
         std::cout << cars.back();
        DrawText(std::to_string(TX).c_str(), 300, 50, 20, RED);
        DrawText(std::to_string(TY).c_str(), 300, 300, 20, RED);
        DrawText(std::to_string(r).c_str(), 50, 50, 20, RED);

        DrawRectangle(EnemyPos.x, EnemyPos.y, 20, 20, RED);
        DrawText("Enemy", EnemyPos.x, EnemyPos.y, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
