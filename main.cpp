#include <stdlib.h>

#include "game.cpp"


void DrawBlocks(Block *block)
{
  // printf("x=%d y=%d w=%d h=%d\n", block->x, block->y, block->width, block->height);
  DrawRectangle(block->x, block->y, block->width, block->height, BLACK);
}

void DrawObjects(Ball *ball, Player *player)
{
  DrawCircle(ball->x, ball->y, ball->radius, BLACK);
  // printf("x=%d y=%d w=%d h=%d\n", player->x, player->y, player->width, player->height);
  DrawRectangle(player->x, player->y, player->width, player->height, RED);
}

int main() {
  InitWindow(800, 600, "raylib basic window");
  
  Player* player = new Player{};
  Ball* ball = new Ball{};
  BallSpeed* speed = new BallSpeed{};
  Block* blocks = new Block[20];

  bool gameOver = false;
  int playerSpeed = 6;
  
  GameInitialization(player, ball, speed, blocks, &gameOver);

  int framesCounter = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Updating
    if (!gameOver){
      moveBall(ball, speed);
      CheckBallCollisions(ball, speed, player, &gameOver);

      if (IsKeyDown(KEY_LEFT))
      {
        player->x -= playerSpeed;
      }
      if (IsKeyDown(KEY_RIGHT))
      {
        player->x += playerSpeed;
      }
    } else {
      if (IsKeyPressed(KEY_SPACE)) GameInitialization(player, ball, speed, blocks, &gameOver); // reinitialize the game if space is typed
    }

    framesCounter++;

    // Drawing
    BeginDrawing();
    ClearBackground(DARKGRAY);

    DrawObjects(ball, player);
    for (int i = 0; i < 20; i++)
    {
      DrawBlocks(&blocks[i]);
    }

    if (gameOver)
    {
      DrawText(
          TextSubtext("* Game Over *", 0, framesCounter/20), 
          (GetScreenWidth() / 2), 
          GetScreenHeight() / 2, 
          30, 
          LIGHTGRAY);
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}