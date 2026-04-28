#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#define TILE_SIZE 40
#define GRID_COLS 20
#define GRID_ROWS 15
#define SCREEN_W  (TILE_SIZE * GRID_COLS)
#define SCREEN_H  (TILE_SIZE * GRID_ROWS)
#define MAX_BLOCKS 32

typedef struct { int col, row; } Block;

static int playerCol = 10;
static int playerRow = 7;

static Block blocks[] = {
    {5, 5}, {6, 5}, {10, 3}, {15, 10}, {3, 8}, {12, 7}
};
static int blockCount = 6;

static int BlockAt(int col, int row) {
    for (int i = 0; i < blockCount; i++)
        if (blocks[i].col == col && blocks[i].row == row) return i;
    return -1;
}

static void TryMove(int dc, int dr) {
    int newCol = playerCol + dc;
    int newRow = playerRow + dr;

    if (newCol < 0 || newCol >= GRID_COLS || newRow < 0 || newRow >= GRID_ROWS) return;

    int bi = BlockAt(newCol, newRow);
    if (bi >= 0) {
        int chain[MAX_BLOCKS];
        int chainLen = 0;
        int cc = newCol, cr = newRow;
        while (true) {
            int idx = BlockAt(cc, cr);
            if (idx < 0) break;
            chain[chainLen++] = idx;
            cc += dc;
            cr += dr;
        }
        int endCol = blocks[chain[chainLen - 1]].col + dc;
        int endRow = blocks[chain[chainLen - 1]].row + dr;
        if (endCol < 0 || endCol >= GRID_COLS || endRow < 0 || endRow >= GRID_ROWS) return;
        for (int i = 0; i < chainLen; i++) {
            blocks[chain[i]].col += dc;
            blocks[chain[i]].row += dr;
        }
    }

    playerCol = newCol;
    playerRow = newRow;
}

static void UpdateFrame(void) {
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))    TryMove(0, -1);
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))  TryMove(0,  1);
    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))  TryMove(-1, 0);
    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) TryMove(1,  0);

    BeginDrawing();
    ClearBackground(BLACK);

    for (int row = 0; row < GRID_ROWS; row++)
        for (int col = 0; col < GRID_COLS; col++)
            DrawRectangleLines(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, (Color){30, 30, 30, 255});

    for (int i = 0; i < blockCount; i++)
        DrawRectangle(blocks[i].col * TILE_SIZE + 4, blocks[i].row * TILE_SIZE + 4, TILE_SIZE - 8, TILE_SIZE - 8, BROWN);

    DrawCircle(
        playerCol * TILE_SIZE + TILE_SIZE / 2,
        playerRow * TILE_SIZE + TILE_SIZE / 2,
        TILE_SIZE / 2 - 4, DARKGREEN
    );

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
