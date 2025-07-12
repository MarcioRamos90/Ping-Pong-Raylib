#include "game.h"


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
    ball->x += speed->x;
    ball->y += speed->y;
}

void CheckBallCollisions(Ball* ball, BallSpeed* speed, Player *player, bool *gameOver)
{
      if ((ball->x >= (GetScreenWidth() - ball->radius)) || (ball->x <= ball->radius))
        speed->x *= -1;
      if (ball->y <= ball->radius)
        speed->y *= -1;

      if (ball->y >= player->y - player->height && //  player height collision varification 
                  (ball->x + ball->radius > player->x && ball->x + ball->radius < player->x + player->width)) //  player width collision boundery varification
        speed->y *= -1;

      if (ball->y >= (GetScreenHeight() - ball->radius))
        *gameOver = true;
}

void GameInitialization(Player *player, Ball* ball, BallSpeed* speed, Block blocks[], bool * gameOver)
{
  player->x = GetScreenWidth() / 2;
  player->y = GetScreenHeight() - PLAYER_HEIGHT;
  player->width = PLAYER_WIDTH;
  player->height = PLAYER_HEIGHT;

  ball->x = GetScreenWidth() / 2;
  ball->y = GetScreenHeight() / 2;
  ball->radius = 20;

  speed->x = 4;
  speed->y = 4;

  InitializeBlocks(blocks);

  *gameOver = false;
}