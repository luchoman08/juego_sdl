#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <SDL/SDL.h>

typedef struct
{
    float X;
    float Y;
} Vector2D;
extern Vector2D puntos;
extern Vector2D PaddlePosition;
extern Vector2D Paddle2Position;
extern Vector2D BallPosition;
extern Vector2D BallDirector;
extern float angulo; //grados
extern float iSecret, iGuess, iDireccion_X;
extern int ScreenSize_W;
extern int ScreenSize_H;
extern double velocidad_adicional;
extern int PaddleSize_W;
extern int PaddleSize_H;
extern int NumberSize_W;
extern int NumberSize_H;
extern int Paddle2Size_W;
extern int Paddle2Size_H;

extern int BallSize_W;
extern int BallSize_H;


extern bool juego_activo;
void InitializeGame();
void UpdatePlayerInput(const SDL_Event * event);
bool UpdateGame(float deltaTime, float currentime);

#endif // GAMESTATE_H_INCLUDED
