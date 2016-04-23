#include "GameState.h"
#include <math.h>
#include <time.h>
Vector2D PaddlePosition;
Vector2D Paddle2Position;
Vector2D BallPosition;
Vector2D BallDirector;
Vector2D puntos;
float angulo;

int ScreenSize_W = 0; // Initalized from screen surface size
int ScreenSize_H = 0;
float iSecret = 180;
int PaddleSize_W = 0; // Initialized from bitmap size
int PaddleSize_H = 0;
int NumberSize_H=0;
int NumberSize_W=0;
int Paddle2Size_W = 0; // Initialized from bitmap size
int Paddle2Size_H = 0;

double velocidad_adicional =1;
int BallSize_W = 0; // Initialized from bitmap size
int BallSize_H = 0;


bool juego_activo = 1;

static int PressingLeft = 0;
static int PressingRight = 0;

static int PressingLeft2 = 0;
static int PressingRight2 = 0;



void InitializeGame()
{
	BallDirector.Y = 1;
    PaddlePosition.X = (ScreenSize_W - PaddleSize_W) / 2;
    PaddlePosition.Y = ScreenSize_H - PaddleSize_H - 40;
    puntos.X = 0;
    puntos.Y = 0;

    /* initialize random seed: */
    srand (time(NULL));

    /* generate secret number between 1 and 10: */
   angulo = abs(rand() % 45 + 80);

    BallDirector.X=rand() % -1 + 1;
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
	/* initialize random seed: */
    srand (time(NULL));
	// arriba
	if(BallPosition.Y - BallSize_H < 0){
		puntos.X++;
		velocidad_adicional/=1.3;
		BallPosition.X = (ScreenSize_W - BallSize_W) / 2;
		BallDirector.Y=-1;
		BallPosition.Y = (ScreenSize_H + BallSize_H)/2;
		 /* initialize random seed: */
    srand (time(NULL));

    /* generate secret number between 1 and 10: */
   angulo = abs(rand() % 45 + 80); 
	}
	
	//abajo
	if(BallPosition.Y + BallSize_W > ScreenSize_H)
	{
		
		puntos.Y++;
		velocidad_adicional/=1.5;
		BallPosition.X = (ScreenSize_W - BallSize_W) / 2;
		BallDirector.Y=1;
		BallPosition.Y = (ScreenSize_H + BallSize_H)/2;

    /* initialize random seed: */
    srand (time(NULL));

    /* generate secret number between 1 and 10: */
   angulo = abs(rand() % 45 + 80);
	}
	//izquierda
	if(BallPosition.X<0){
	/* generate secret number between 1 and 10: */
	
	BallDirector.X *=-1;
	angulo = rand() % 30 + 60;
	BallPosition.X += 8;
	}
	//derecha
	if(BallPosition.X + BallSize_H>ScreenSize_W){
	/* initialize random seed: */
	BallDirector.X *=-1;
	angulo = rand() % 30 + 50;	
	BallPosition.X -= 8;
	}
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
void rebotar_raqueta(Vector2D *raqueta)
{   
	
	if(  BallPosition.X  + BallSize_W > raqueta->X  && //borde izquierdo de la raqueta
		 BallPosition.X - BallSize_W   < raqueta->X + PaddleSize_W && //borde derecho de la raqueta
		 BallPosition.Y < raqueta->Y + PaddleSize_H && //borde inferior de la raqueta)
		 BallPosition.Y + BallSize_H > raqueta->Y  ) //borde superior de la raqueta)
	{
		if(raqueta == &PaddlePosition)
	{
		raqueta->Y+=5;
	}
	if(raqueta == &Paddle2Position)
	{
		raqueta->Y-=5;
	}
		angulo = 45;
		 if ((PressingLeft || PressingLeft2) && BallDirector.X==1){

         BallDirector.X=-1;
         BallDirector.Y=-1;


      
	}

    if ((PressingRight || PressingRight2) && BallDirector.X==-1){


        BallDirector.X=1;
	    BallDirector.Y=-1;
	    
   
	}
	else{
      BallDirector.X*=1;
	  BallDirector.Y*=-1;
	}
	velocidad_adicional+=0.2;
	}
	 
}


bool UpdateGame(float deltaTime, float currentime)
{
    const float PaddleSpeed = 400.0f;
    const float BallSpeed = 200.0f;
    
    BallPosition.X += BallDirector.X * (BallSpeed * deltaTime) * velocidad_adicional * cos((angulo*M_PI)/180);
    BallPosition.Y += BallDirector.Y * (BallSpeed * deltaTime) * velocidad_adicional * sin((angulo*M_PI)/180);
    limites_pantalla();
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
	
		rebotar_raqueta(&PaddlePosition);
		rebotar_raqueta(&Paddle2Position);
		if((int)(currentime *1000 )% 3 == 0){
		PaddlePosition.Y = ScreenSize_H - PaddleSize_H - 40;
        Paddle2Position.Y = 40;
	}
		if(puntos.X>=0)
		return false;
		else
		return true;
}
