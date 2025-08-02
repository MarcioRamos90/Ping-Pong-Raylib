#include <stdlib.h>
#include <raylib.h>
#include <cstdio>
#include <cmath>
#include <random>

#include "game.cpp"
#include "utils.cpp"

void DrawBlocks(Block *block)
{
  // printf("x=%d y=%d w=%d h=%d\n", block->x, block->y, block->width, block->height);
  DrawRectangle(block->x, block->y, block->width, block->height,  block->color);
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
  BallSpeed* ballSpeed = new BallSpeed{4, 4};
  Block* blocks = new Block[20];

  GameState *gameState = new GameState{};

  int playerSpeed = 6;
  
  GameInitialization(player, ball, ballSpeed, gameState);
  InitializeBlocks(blocks);

  int framesCounter = 0;
  float t = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Updating
    if (!gameState->gameOver && !gameState->paused){
      moveBall(ball, ballSpeed);
      CheckBallCollisions(ball, ballSpeed, player, gameState);
      ControlPlayerKeys(player, playerSpeed);
      checkBlocksCollision(blocks, ballSpeed, ball, gameState);
    } else {
      if (IsKeyPressed(KEY_SPACE)) {
        if (gameState->gameOver) {
          GameInitialization(player, ball, ballSpeed, gameState); // reinitialize the game if space is typed
          InitializeBlocks(blocks);
        } 
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
      if (blocks[i].health > 0) {
        DrawBlocks(&blocks[i]);
      }
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