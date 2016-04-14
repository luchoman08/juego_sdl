#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <SDL/SDL.h>

typedef struct
{
    float X;
    float Y;
} Vector2D;

extern Vector2D PaddlePosition;
extern Vector2D BallPosition;

extern int ScreenSize_W;
extern int ScreenSize_H;

extern int PaddleSize_W;
extern int PaddleSize_H;

extern int BallSize_W;
extern int BallSize_H;

void InitializeGame();
void UpdatePlayerInput(const SDL_Event * event);
void UpdateGame(float deltaTime);

#endif // GAMESTATE_H_INCLUDED
