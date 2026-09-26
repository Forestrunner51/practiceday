#include <raylib.h>
#include <raymath.h>

#include <algorithm>
#include <random>
#include <vector>

namespace {

constexpr int kScreenWidth = 800;
constexpr int kScreenHeight = 600;
constexpr int kCoinCount = 5;

struct Player {
    Vector2 pos{};
    float radius = 14.0f;
    float speed = 220.0f;
};

struct Coin {
    Vector2 pos{};
    float radius = 8.0f;
};

struct Enemy {
    Vector2 pos{};
    float radius = 12.0f;
    float speed = 80.0f;
};

class Game {
public:
    Game() { Reset(); }

    void Update(float dt) {
        if (gameOver_) {
            if (IsKeyPressed(KEY_ENTER)) Reset();
            return;
        }

        Vector2 dir{};
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) dir.y -= 1.0f;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) dir.y += 1.0f;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) dir.x -= 1.0f;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dir.x += 1.0f;

        // Normalize so diagonal movement isn't faster
        player_.pos = Vector2Add(player_.pos, Vector2Scale(Vector2Normalize(dir), player_.speed * dt));
        player_.pos.x = std::clamp(player_.pos.x, player_.radius, kScreenWidth - player_.radius);
        player_.pos.y = std::clamp(player_.pos.y, player_.radius, kScreenHeight - player_.radius);

        for (auto& e : enemies_) {
            Vector2 toPlayer = Vector2Normalize(Vector2Subtract(player_.pos, e.pos));
            e.pos = Vector2Add(e.pos, Vector2Scale(toPlayer, e.speed * dt));
            if (CheckCollisionCircles(player_.pos, player_.radius, e.pos, e.radius)) gameOver_ = true;
        }

        std::erase_if(coins_, [&](const Coin& c) {
            if (!CheckCollisionCircles(player_.pos, player_.radius, c.pos, c.radius)) return false;
            ++score_;
            if (score_ % 5 == 0) SpawnEnemy();
            return true;
        });
        while (coins_.size() < kCoinCount) SpawnCoin();
    }

    void Draw() const {
        ClearBackground(Color{42, 59, 42, 255});

        for (const auto& c : coins_) DrawCircleV(c.pos, c.radius, GOLD);
        for (const auto& e : enemies_) DrawCircleV(e.pos, e.radius, RED);
        DrawCircleV(player_.pos, player_.radius, SKYBLUE);

        DrawText(TextFormat("Score: %d", score_), 12, 12, 20, RAYWHITE);

        if (gameOver_) {
            DrawRectangle(0, 0, kScreenWidth, kScreenHeight, Fade(BLACK, 0.6f));
            DrawCentered("Game Over", kScreenHeight / 2 - 30, 40);
            DrawCentered("Press Enter to restart", kScreenHeight / 2 + 20, 20);
        }
    }

private:
    static void DrawCentered(const char* text, int y, int fontSize) {
        DrawText(text, (kScreenWidth - MeasureText(text, fontSize)) / 2, y, fontSize, RAYWHITE);
    }

    float Rand(float min, float max) { return std::uniform_real_distribution<float>(min, max)(rng_); }

    void SpawnCoin() {
        coins_.push_back({{Rand(20, kScreenWidth - 20), Rand(20, kScreenHeight - 20)}});
    }

    void SpawnEnemy() {
        // Spawn on a random edge so enemies don't appear on top of the player
        Vector2 pos{};
        switch (std::uniform_int_distribution<int>(0, 3)(rng_)) {
            case 0: pos = {0, Rand(0, kScreenHeight)}; break;
            case 1: pos = {kScreenWidth, Rand(0, kScreenHeight)}; break;
            case 2: pos = {Rand(0, kScreenWidth), 0}; break;
            default: pos = {Rand(0, kScreenWidth), kScreenHeight}; break;
        }
        enemies_.push_back({.pos = pos, .speed = Rand(60, 110)});
    }

    void Reset() {
        player_ = Player{.pos = {kScreenWidth / 2.0f, kScreenHeight / 2.0f}};
        coins_.clear();
        enemies_.clear();
        score_ = 0;
        gameOver_ = false;
        for (int i = 0; i < kCoinCount; ++i) SpawnCoin();
        for (int i = 0; i < 2; ++i) SpawnEnemy();
    }

    std::mt19937 rng_{std::random_device{}()};
    Player player_;
    std::vector<Coin> coins_;
    std::vector<Enemy> enemies_;
    int score_ = 0;
    bool gameOver_ = false;
};

}  // namespace

int main() {
    InitWindow(kScreenWidth, kScreenHeight, "Top-Down Game");
    SetTargetFPS(60);

    Game game;
    while (!WindowShouldClose()) {
        game.Update(GetFrameTime());
        BeginDrawing();
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
