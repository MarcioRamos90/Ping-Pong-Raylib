#include "game.h"

bool pause = false;


void InitializeBlocks(Block blocks[])
{
  int x = 1;
  int y = 0;
  int min = 10;

  for (int i = 0; i < 20; i++)
  {
    if (i >= min) {
      min *= 2;
      y++; 
      x = 1;
    }
    blocks[i] = Block{x * (BOCK_WIDTH + 15), (y * 30) + 20, BOCK_WIDTH, BOCK_HEIGHT};
    x++;
  }
  
}

void moveBall(Ball* ball, BallSpeed* speed)
{
  if (!pause) {
    ball->x += speed->x;
    ball->y += speed->y;
  }
}

void CheckBallCollisions(Ball* ball, BallSpeed* speed, Player *player, GameState *gameState)
{
      if ((ball->x >= (GetScreenWidth() - ball->radius)) || (ball->x <= ball->radius))
        speed->x *= -1;
      if (ball->y <= ball->radius)
      {
        speed->y *= -1;
      }

      if (
            ball->y - ball->radius >= (player->y - player->height) // top
        && (ball->y - ball->radius <= player->y + player->height) // down
        && (ball->x + ball->radius >= player->x) // left
        && (ball->x - ball->radius <= player->x + player->width) // right
      )
      {
        speed->y *= -1;
        ball->color = GREEN;
      } else {
        ball->color = BLUE;
      }

      if (ball->y >= (GetScreenHeight() - ball->radius))
        gameState->gameOver = true;
}

void GameInitialization(Player *player, Ball* ball, BallSpeed* speed, Block blocks[], GameState * gameState)
{
  player->x = GetScreenWidth() / 2;
  player->y = GetScreenHeight() - PLAYER_HEIGHT;
  player->width = PLAYER_WIDTH;
  player->height = PLAYER_HEIGHT;

  ball->x = GetScreenWidth() / 2;
  ball->y = GetScreenHeight() / 2;
  ball->radius = 10;
  ball->color = BLUE;

  speed->x = 4;
  speed->y = 4;

  InitializeBlocks(blocks);

  gameState->gameOver = false;
  gameState->paused = false;
  gameState->win = false;

}