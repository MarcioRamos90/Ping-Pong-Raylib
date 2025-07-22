#include <stdlib.h>
#include "raylib.h"
#include <cstdio>

#include "math.cpp"
#include "game.cpp"

void DrawBlocks(Block *block)
{
  // printf("x=%d y=%d w=%d h=%d\n", block->x, block->y, block->width, block->height);
  DrawRectangle(block->x, block->y, block->width, block->height, BLACK);
}

void DrawObjects(Ball *ball, Player *player)
{
  DrawCircle(ball->x, ball->y, ball->radius, ball->color);
  // printf("x=%d y=%d w=%d h=%d\n", player->x, player->y, player->width, player->height);
  DrawRectangle(player->x, player->y, player->width, player->height, RED);
}

void ControlPlayerKeys(Player *player, int playerSpeed)
{
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
  {
    player->x -= playerSpeed;
  }
  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
  {
    player->x += playerSpeed;
  }
  if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
  {
    player->y -= playerSpeed;
  }
  if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
  {
    player->y += playerSpeed;
  }
}

int main() {
  InitWindow(800, 600, "raylib basic window");
  
  Player* player = new Player{};
  Ball* ball = new Ball{};
  BallSpeed* speed = new BallSpeed{};
  Block* blocks = new Block[20];

  GameState *gameState = new GameState{};

  int playerSpeed = 6;
  
  GameInitialization(player, ball, speed, blocks, gameState);

  int framesCounter = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Updating
    if (!gameState->gameOver){
      moveBall(ball, speed);
      CheckBallCollisions(ball, speed, player, gameState);
      ControlPlayerKeys(player, playerSpeed);
    } else {
      if (IsKeyPressed(KEY_SPACE)) {
        if (gameState->gameOver) GameInitialization(player, ball, speed, blocks, gameState); // reinitialize the game if space is typed
        else
        {
          pause = !pause;
        }
      } 
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

    if (gameState->gameOver)
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