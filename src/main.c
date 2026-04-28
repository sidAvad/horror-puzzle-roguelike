#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#define TILE_SIZE 40
#define GRID_COLS 20
#define GRID_ROWS 15
#define SCREEN_W (TILE_SIZE * GRID_COLS)
#define SCREEN_H (TILE_SIZE * GRID_ROWS)

static int playerCol = 10;
static int playerRow = 7;

static void UpdateFrame(void) {
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))    playerRow--;
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))  playerRow++;
    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))  playerCol--;
    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) playerCol++;

    if (playerCol < 0) playerCol = 0;
    if (playerCol >= GRID_COLS) playerCol = GRID_COLS - 1;
    if (playerRow < 0) playerRow = 0;
    if (playerRow >= GRID_ROWS) playerRow = GRID_ROWS - 1;

    BeginDrawing();
    ClearBackground(BLACK);

    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            DrawRectangleLines(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, (Color){30, 30, 30, 255});
        }
    }

    DrawRectangle(playerCol * TILE_SIZE + 4, playerRow * TILE_SIZE + 4, TILE_SIZE - 8, TILE_SIZE - 8, DARKGREEN);

    EndDrawing();
}

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "Horror Puzzle Roguelike");
    SetTargetFPS(60);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateFrame, 0, 1);
#else
    while (!WindowShouldClose()) UpdateFrame();
    CloseWindow();
#endif

    return 0;
}
