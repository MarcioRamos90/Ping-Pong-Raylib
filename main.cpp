#include <stdlib.h>
#include <raylib.h>
#include <cstdio>
#include <cmath>
#include <random>

#include "math.cpp"
#include "game.cpp"
#include "utils.cpp"

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
  std::random_device rd;  // seed
  std::mt19937 gen(rd()); // Mersenne Twister RNG
  std::uniform_int_distribution<> dis(-1, 1);

  InitWindow(800, 600, "raylib basic window");
  
  Player* player = new Player{};
  Ball* ball = new Ball{};
  BallSpeed* speed = new BallSpeed{dis(gen) * 4, dis(gen) * 4};
  Block* blocks = new Block[20];

  GameState *gameState = new GameState{};

  int playerSpeed = 6;
  
  GameInitialization(player, ball, blocks, gameState);

  int framesCounter = 0;
  float t = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Updating
    if (!gameState->gameOver && !gameState->paused){
      moveBall(ball, speed);
      CheckBallCollisions(ball, speed, player, gameState);
      ControlPlayerKeys(player, playerSpeed);
    } else {
      if (IsKeyPressed(KEY_SPACE)) {
        if (gameState->gameOver) GameInitialization(player, ball, blocks, gameState); // reinitialize the game if space is typed
        else
        {
          gameState->paused = !gameState->paused;
        }
      } 
    }

    t += 0.1;
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
      writeTextInScreenAtCenter("* Game Over *", 30, 2, 0, 0);
      if (sin(t) > 0) writeTextInScreenAtCenter("Press SPACE to restart", 30, 2, 0, 100);

    }

    if (gameState->statingGame)
    {

      writeTextInScreenAtCenter("Game Start", 30, 2, 0, 0);
      if (sin(t) > 0) writeTextInScreenAtCenter("Press SPACE to start", 30, 2, 0, 100);
      gameState->paused = true;

      if (IsKeyPressed(KEY_SPACE)) {
        gameState->paused = false;
        gameState->statingGame = false;
      }
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}