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
    blocks[i] = Block{
                    x * (BOCK_WIDTH + 15), 
                    (y * 30) + 20, 
                    BOCK_WIDTH, 
                    BOCK_HEIGHT, 
                    1, 
                    YELLOW
                };
    x++;
  }
  
}

void moveBall(Ball* ball, BallSpeed* ballSpeed)
{
    ball->x += ballSpeed->x;
    ball->y += ballSpeed->y;
}

void checkBlocksCollision(Block blocks[], BallSpeed *ballSpeed, Ball *ball, GameState *gameState)
{

  for (int x = 0; x < 20; x++) {
    if (blocks[x].health > 0 &&
        ball->y - ball->radius >= (blocks[x].y - blocks[x].height)    // top
        && (ball->y - ball->radius <= blocks[x].y + blocks[x].height) // down
        && (ball->x + ball->radius >= blocks[x].x)                  // left
        && (ball->x - ball->radius <= blocks[x].x + blocks[x].width)  // right
    )
    {
      blocks[x].color = RED;
      blocks[x].health--;
      ballSpeed->y *= -1;
    } else {
      ball->color = BLUE;
    }
  }
  
  
}

void CheckBallCollisions(Ball* ball, BallSpeed *ballSpeed, Player *player, GameState *gameState)
{
      if ((ball->x >= (GetScreenWidth() - ball->radius)) || (ball->x <= ball->radius))
        ballSpeed->x *= -1;
      if (ball->y <= ball->radius)
      {
        ballSpeed->y *= -1;
      }

      if (
            ball->y - ball->radius >= (player->y - player->height) // top
        && (ball->y - ball->radius <= player->y + player->height) // down
        && (ball->x + ball->radius >= player->x) // left
        && (ball->x - ball->radius <= player->x + player->width) // right
      )
      {
        ballSpeed->y *= -1;
        ball->color = GREEN;
      } else {
        ball->color = BLUE;
      }

      if (ball->y >= (GetScreenHeight() - ball->radius))
        gameState->gameOver = true;
}

void GameInitialization(Player *player, Ball* ball, BallSpeed* ballSpeed, GameState * gameState)
{
  std::random_device rd;  // seed
  std::mt19937 gen(rd()); // Mersenne Twister RNG
  std::uniform_int_distribution<> dis(0, 1);

  int value = dis(gen) == 0 ? -1 : 1;
  ballSpeed->x = value;
  ballSpeed->y = 4;
  printf("x=%d, y=%d\n", ballSpeed->x, ballSpeed->y);

  player->x = GetScreenWidth() / 2;
  player->y = GetScreenHeight() - PLAYER_HEIGHT;
  player->width = PLAYER_WIDTH;
  player->height = PLAYER_HEIGHT;

  ball->x = GetScreenWidth() / 2;
  ball->y = GetScreenHeight() / 2;
  ball->radius = 10;
  ball->color = BLUE;

  gameState->gameOver = false;
  gameState->paused = false;
  gameState->win = false;
  gameState->statingGame = true;
}