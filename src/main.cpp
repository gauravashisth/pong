#include <raylib.h>

int main() {
  InitWindow(800, 600, "Hello, Raylib!");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Welcome to Raylib!", 300, 280, 20, DARKGRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
