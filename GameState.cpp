#include "GameState.h"

Vector2D PaddlePosition;
Vector2D Paddle2Position;
Vector2D BallPosition;
Vectir2D BallDirection;
int ScreenSize_W = 0; // Initalized from screen surface size
int ScreenSize_H = 0;

int PaddleSize_W = 0; // Initialized from bitmap size
int PaddleSize_H = 0;

int Paddle2Size_W = 0; // Initialized from bitmap size
int Paddle2Size_H = 0;

double velocidad_adicional =1;
int BallSize_W = 0; // Initialized from bitmap size
int BallSize_H = 0;
double direccion_y = 1;
bool juego_activo = 1;
double direccion_x = 1;
static int PressingLeft = 0;
static int PressingRight = 0;

static int PressingLeft2 = 0;
static int PressingRight2 = 0;
int vidas =3;
void InitializeGame()
{
    PaddlePosition.X = (ScreenSize_W - PaddleSize_W) / 2;
    PaddlePosition.Y = ScreenSize_H - PaddleSize_H - 40;
    
    Paddle2Position.X = PaddlePosition.X;
    Paddle2Position.Y = 40;
    
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
        
        //player 2
        
      if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_q)
        PressingLeft2 = 1;

    if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_q)
        PressingLeft2 = 0;

    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_e)
        PressingRight2 = 1;

    if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_e)
        PressingRight2 = 0;   
}
void limites_pantalla()
{
	if(BallPosition.Y - BallSize_H < 0)
	direccion_y*=-1;
	
	if(BallPosition.Y + BallSize_W > ScreenSize_H)
	{
		
		vidas--;
		velocidad_adicional=1;
		BallPosition.X = (ScreenSize_W - BallSize_W) / 2;
		direccion_y=1;
		BallPosition.Y = 0+BallSize_H;
	
	}
	
	if(BallPosition.X<0)
	direccion_x *=-1;
	if(BallPosition.X + BallSize_H>ScreenSize_W)
	direccion_x *=-1;

	
}
bool limite_raqueta()
{
	if(PaddlePosition.X  <0){
	PaddlePosition.X +=2;
	return false;
	}
	if(PaddlePosition.X + PaddleSize_W > ScreenSize_W){
	PaddlePosition.X -=2;
	return false;
	}
	else 
	return true;
}
bool limite_raqueta2()
{
	if(Paddle2Position.X  <0){
	Paddle2Position.X +=2;
	return false;
	}
	if(Paddle2Position.X + PaddleSize_W > ScreenSize_W){
	Paddle2Position.X -=2;
	return false;
	}
	else 
	return true;
}
void rebotar_raqueta()
{   
  
	if(  BallPosition.X  + BallSize_W > PaddlePosition.X  && //borde izquierdo de la raqueta
		 BallPosition.X - BallSize_W   < PaddlePosition.X + PaddleSize_W && //borde derecho de la raqueta
		 BallPosition.Y + BallSize_H > PaddlePosition.Y  ) //borde superior de la raqueta)
	{
		velocidad_adicional+=0.2;
		 if (PressingLeft && direccion_x==1){
		 BallPosition.Y-=2;
		 BallPosition.X-=2;
         direccion_x=-1;
         direccion_y=-1;
	}

    if (PressingRight && direccion_x==-1){
		BallPosition.Y-=2;
		BallPosition.X+=2;
      direccion_x=1;
	  direccion_y=-1;
	  
	  
	}
	else{
      direccion_x*=1;
	  direccion_y*=-1;
	}
	
	}
	 
}
//~ void sacudida_raqueta()
//~ {
	//~ Vector2D pos_inicial;
	//~ pos_inicial.X = PaddlePosition.X;
	//~ pos_inicial.Y = PaddlePosition.Y;
	//~ PaddlePosition.X
	//~ 
//~ }

bool UpdateGame(float deltaTime)
{
    const float PaddleSpeed = 400.0f;
    const float BallSpeed = 200.0f;

    BallPosition.X += direccion_x*(BallSpeed * deltaTime) * velocidad_adicional;
    BallPosition.Y += direccion_y*(BallSpeed * deltaTime) * velocidad_adicional;
    if(limite_raqueta()){
		if (PressingLeft){
			PaddlePosition.X -= PaddleSpeed * deltaTime;
		}
			
		
		if (PressingRight){
			PaddlePosition.X += PaddleSpeed * deltaTime;
		 
		}
		
		
	}
	if(limite_raqueta2())
	{
		if (PressingLeft2){
			Paddle2Position.X -= PaddleSpeed * deltaTime;
		}
			
		
		if (PressingRight2){
			Paddle2Position.X += PaddleSpeed * deltaTime;
		 
		}
	}
	limites_pantalla();
		rebotar_raqueta();
		if(vidas>=0)
		return false;
		else
		return true;
}
