#include <raylib.h>

int main() {
  const int screen_w = 1280;
  const int screen_h = 800;

  InitWindow(screen_w, screen_h, "PONG");
  SetTargetFPS(60);

  // game loop
  while (WindowShouldClose() == false) {
    // created a blank canvas
    BeginDrawing();
    DrawCircle(screen_w / 2, screen_h / 2, 20, WHITE);
    // y=screen_h/2-rectangle_h/2
    DrawRectangle(10, (screen_h / 2) - 60, 25, 120, WHITE);
    DrawLine(screen_w / 2, 0, screen_w / 2, screen_h, WHITE);
    DrawRectangle(screen_w - 35, (screen_h / 2) - 60, 25, 120, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
