#include <raylib.h>

class Ball {
public:
  int x, y;
  int speed_x, speed_y;
  int radius;

  void Draw() { DrawCircle(x, y, radius, WHITE); }
  void speed() {
    x += speed_x;
    y += speed_y;
  }
};

Ball ball;

int main() {
  const int screen_w = 1280;
  const int screen_h = 800;

  InitWindow(screen_w, screen_h, "PONG");
  SetTargetFPS(60);

  ball.radius = 20;
  ball.x = screen_w / 2;
  ball.y = screen_h / 2;
  ball.speed_x = 7;
  ball.speed_y = 7;

  // game loop
  while (!WindowShouldClose()) {
    // created a blank canvas
    BeginDrawing();
    /*DrawCircle(screen_w / 2, screen_h / 2, 20, WHITE);*/
    // update
    ball.speed();
    ClearBackground(BLANK);

    // dividers
    DrawLine((screen_w / 2) - 5, 0, (screen_w / 2) - 5, screen_h, WHITE);
    DrawLine((screen_w / 2) + 5, 0, (screen_w / 2) + 5, screen_h, WHITE);

    // draws ball
    ball.Draw();

    // paddles, y=screen_h/2 - rectangle_h/2
    DrawRectangle(10, (screen_h / 2) - 60, 25, 120, WHITE);
    DrawRectangle(screen_w - 35, (screen_h / 2) - 60, 25, 120, WHITE);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
