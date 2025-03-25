#include <iostream>
#include <raylib.h>

#ifdef __APPLE__
#include <ApplicationServices/ApplicationServices.h> // macOS Framework
#elif __linux__
#define Font XFont
#include <X11/Xlib.h> // Linux X11 Library
#endif

int ai_score = 0;
int p_score = 0;

// input: rgb values+ alpha channel (transparency)
Color Green = Color{26, 131, 110, 50};
Color Dgreen = Color{20, 160, 133, 55};
Color Lgreen = Color{129, 204, 184, 50};
Color Yellow = Color{243, 213, 91, 255};

class ScreenInfo {
public:
  // Struct to hold resolution values
  struct Resolution {
    int width;
    int height;
  };

  // Function to get actual screen resolution
  static Resolution getScreenResolution() {
    Resolution res = {0, 0}; // Default values

#ifdef __APPLE__
                             // macOS Code
    CGDirectDisplayID mainDisplay = CGMainDisplayID();
    res.width = CGDisplayPixelsWide(mainDisplay);
    res.height = CGDisplayPixelsHigh(mainDisplay);

#elif __linux__
                             // Linux Code
    Display *display = XOpenDisplay(nullptr);
    if (display == nullptr) {
      std::cerr << "Unable to open X display" << '\n';
      return res;
    }

    Screen *screen = DefaultScreenOfDisplay(display);
    res.width = screen->width;
    res.height = screen->height;

    XCloseDisplay(display);
#endif

    return res;
  }

  // Function to return 71% of screen resolution
  static Resolution getScaledResolution() {
    Resolution res = getScreenResolution();
    return {static_cast<int>(res.width * 0.762),
            static_cast<int>(res.height * 0.762)};
  }
};

class Ball {
public:
  int x, y;
  int speed_x, speed_y;
  int radius;

  void Draw() { DrawCircle(x, y, radius, Yellow); }
  void speed() {
    x += speed_x;
    y += speed_y;

    // collision edges for ball
    if (y + radius >= GetScreenHeight() || y - radius <= 0)
      speed_y *= -1;
    /*if (x + radius >= GetScreenHeight() || x - radius <= 0)*/
    /*  speed_x *= -1;*/
    if (x + radius >= GetScreenWidth()) { // ai score
      ai_score++;
      reset();
    }
    if (x - radius <= 0) { // player score
      p_score++;
      reset();
    }
  }

  // resets the game after scoring a point
  void reset() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    // randomize the direction of ball at starting point
    int choices[2] = {-1, 1};
    speed_x *= choices[GetRandomValue(0, 1)];
    speed_y *= choices[GetRandomValue(0, 1)];
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
  float x, y;
  float width, height;
  float speed;

  // draws rectangle w/ rounded edges
  void Draw() {
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
  }
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
  ScreenInfo::Resolution fullRes = ScreenInfo::getScreenResolution();
  ScreenInfo::Resolution scaledRes = ScreenInfo::getScaledResolution();
  int screen_w = scaledRes.width;
  int screen_h = scaledRes.height;

  InitWindow(screen_w, screen_h, "Pong");
  SetTargetFPS(60);

  ball.radius = 20;
  ball.x = screen_w / 2;
  ball.y = screen_h / 2;
  ball.speed_x = 8;
  ball.speed_y = 8;

  player.width = 25;
  player.height = 120;
  player.x = screen_w - player.width - 10;
  player.y = screen_h / 2 - player.height / 2;
  player.speed = 8;

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

    // collision
    if (CheckCollisionCircleRec(
            Vector2{static_cast<float>(ball.x), static_cast<float>(ball.y)},
            ball.radius,
            Rectangle{static_cast<float>(player.x),
                      static_cast<float>(player.y),
                      static_cast<float>(player.width),
                      static_cast<float>(player.height)})) {
      ball.speed_x *= -1;
    }
    if (CheckCollisionCircleRec(
            Vector2{static_cast<float>(ball.x), static_cast<float>(ball.y)},
            ball.radius,
            Rectangle{static_cast<float>(ai.x), static_cast<float>(ai.y),
                      static_cast<float>(ai.width),
                      static_cast<float>(ai.height)})) {
      ball.speed_x *= -1;
    }

    // ui
    ClearBackground(Dgreen);
    DrawRectangle(screen_w / 2, 0, screen_w / 2, screen_h, Green);
    DrawCircle(screen_w / 2, screen_h / 2, 150, Lgreen);

    // dividers
    DrawLine((screen_w / 2) - 5, 0, (screen_w / 2) - 5, screen_h, WHITE);
    DrawLine((screen_w / 2) + 5, 0, (screen_w / 2) + 5, screen_h, WHITE);

    // paddles
    player.Draw();
    ai.Draw();

    // convert p,ai_score to text
    DrawText(TextFormat("%i", ai_score), screen_w / 4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", p_score), 3 * screen_w / 4 - 20, 20, 80, WHITE);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
