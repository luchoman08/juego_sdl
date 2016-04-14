#include "GameState.h"

Vector2D PaddlePosition;
Vector2D BallPosition;

int ScreenSize_W = 0; // Initalized from screen surface size
int ScreenSize_H = 0;

int PaddleSize_W = 0; // Initialized from bitmap size
int PaddleSize_H = 0;

int BallSize_W = 0; // Initialized from bitmap size
int BallSize_H = 0;
int direccion_y = 1;
int direccion_x = 1;
static int PressingLeft = 0;
static int PressingRight = 0;

void InitializeGame()
{
    PaddlePosition.X = (ScreenSize_W - PaddleSize_W) / 2;
    PaddlePosition.Y = ScreenSize_H - PaddleSize_H - 40;

    BallPosition.X = (ScreenSize_W - BallSize_W) / 2;
    BallPosition.Y = ScreenSize_H / 2;
}

void UpdatePlayerInput(const SDL_Event * event)
{
    if (!event)
        return;

    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_LEFT)
        PressingLeft = 1;

    if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_LEFT)
        PressingLeft = 0;

    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_RIGHT)
        PressingRight = 1;

    if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_RIGHT)
        PressingRight = 0;
}
void limites_pantalla()
{
	if(BallPosition.Y - BallSize_H < 0)
	direccion_y*=-1;
	
	if(BallPosition.Y + BallSize_W > ScreenSize_H)
	direccion_y*=-1;
	
	if(BallPosition.X<0)
	direccion_x *=-1;
	if(BallPosition.X + BallSize_H>ScreenSize_W)
	direccion_x *=-1;
}
void rebotar_raqueta()
{   
	
	if(  BallPosition.X + BallSize_W/2  > PaddlePosition.X - PaddleSize_W/2 && //borde izquierdo de la raqueta
		 BallPosition.X - BallSize_W/2   < PaddlePosition.X + PaddleSize_W && //borde derecho de la raqueta
		 BallPosition.Y + BallSize_H/2 > PaddlePosition.Y - PaddleSize_H/2 ) //borde superior de la raqueta)
	{
		 if (PressingLeft && direccion_x==1){
         direccion_x*=-1;
         direccion_y*=-1;
	}

    if (PressingRight && direccion_x==-1){
      direccion_x*=-1;
	  direccion_y*=-1;
	}
	else{
      direccion_x*=1;
	  direccion_y*=-1;
	}
	
	}
	 
}


void UpdateGame(float deltaTime)
{
    const float PaddleSpeed = 200.0f;
    const float BallSpeed = 250.0f;

    BallPosition.X += direccion_x*(BallSpeed * deltaTime);
    BallPosition.Y += direccion_y*(BallSpeed * deltaTime);
    if (PressingLeft){
        PaddlePosition.X -= PaddleSpeed * deltaTime;
	}
        
    limites_pantalla();
    rebotar_raqueta();
    if (PressingRight){
        PaddlePosition.X += PaddleSpeed * deltaTime;
     
	}
}
