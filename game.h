#include "raylib.h"

const int PLAYER_HEIGHT = 20;
const int PLAYER_WIDTH = 70;

const int BOCK_HEIGHT = 20;
const int BOCK_WIDTH = 50;

typedef struct Ball {
  int x;
  int y;
  int radius;
} Ball;

typedef struct BallSpeed {
  int x;
  int y;
} BallSpeed;

typedef struct Player {
  int x;
  int y;
  int width;
  int height;
} Player;

typedef struct Block {
  int x;
  int y;
  int width;
  int height;
} Block;

void InitializeBlocks(Block blocks[]);
void moveBall(Ball *ball, BallSpeed *speed);
void CheckBallCollisions(Ball *ball, BallSpeed *speed, Player *player);
void GameInitialization(Player *player, Ball *ball, BallSpeed *speed, Block blocks[], bool *gameOver);