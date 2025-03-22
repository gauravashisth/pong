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

    // collision edges for ball
    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
      speed_y *= -1;
    }
    if (x + radius >= GetScreenWidth() || x - radius <= 0) {
      speed_x *= -1;
    }
  }
};

class Paddle {
protected:
  void restrictedMoves() {
    // it stops paddle to move outside of screen
    if (y <= 0) {
      y = 0;
    }
    if (y + height >= GetScreenHeight()) {
      y = GetScreenHeight() - height;
    }
  }

public:
  int x, y;
  int width, height;
  int speed;

  void Draw() { DrawRectangle(x, y, width, height, WHITE); }
  void Update() {
    // here IsKeyUp() isn't used 'cause it makes paddle to move upward w/o input
    if (IsKeyDown(KEY_UP)) {
      y -= speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
      y += speed;
    }
    restrictedMoves();
  }
};

class aiPaddlle : public Paddle {
public:
  void Update(int ball_y) {
    // handle aiPaddle movements
    if (y + height / 2 > ball_y) {
      y -= speed;
    }
    if (y + height / 2 < ball_y) {
      y += speed;
    }
    restrictedMoves();
  }
};

Ball ball;
Paddle player;
aiPaddlle ai;

int main() {
  const int screen_w = 1280;
  const int screen_h = 800;

  InitWindow(screen_w, screen_h, "Pong");
  SetTargetFPS(60);

  ball.radius = 20;
  ball.x = screen_w / 2;
  ball.y = screen_h / 2;
  ball.speed_x = 10;
  ball.speed_y = 10;

  player.width = 25;
  player.height = 120;
  player.x = screen_w - player.width - 10;
  player.y = screen_h / 2 - player.height / 2;
  player.speed = 6;

  ai.width = 25;
  ai.height = 120;
  ai.x = 10;
  ai.y = screen_h / 2 - ai.height / 2;
  ai.speed = 6;

  // game loop
  while (!WindowShouldClose()) {
    // created a blank canvas
    BeginDrawing();
    // draws ball
    ball.Draw();
    ball.speed();

    // update
    player.Update();
    ai.Update(ball.y);
    ClearBackground(BLANK);

    // dividers
    DrawLine((screen_w / 2) - 5, 0, (screen_w / 2) - 5, screen_h, WHITE);
    DrawLine((screen_w / 2) + 5, 0, (screen_w / 2) + 5, screen_h, WHITE);

    // paddles
    player.Draw();
    ai.Draw();

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
