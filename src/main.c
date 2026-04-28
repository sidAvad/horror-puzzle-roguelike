#include "raylib.h"

int main(void) {
    InitWindow(800, 600, "Horror Puzzle Roguelike");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Horror Puzzle Roguelike", 200, 270, 30, DARKGREEN);
        DrawText("It begins...", 320, 320, 20, GRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
