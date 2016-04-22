#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include "GameGraphics.h"
#include "GameState.h"

SDL_Surface* PaddleGraphic1 = 0;
SDL_Surface* PaddleGraphic2 = 0;
SDL_Surface* BallGraphic = 0;
SDL_Surface* Life1 = 0;
SDL_Surface* Life2 = 0;
SDL_Surface* Life3 = 0;
SDL_Surface* Fondo = 0;
//numeros
SDL_Surface* Number0 = 0;
SDL_Surface* Number1 = 0;
SDL_Surface* Number2 = 0;
SDL_Surface* Number3 = 0;
SDL_Surface* Number4 = 0;
SDL_Surface* Number5 = 0;
SDL_Surface* Number6 = 0;
SDL_Surface* Number7 = 0;
SDL_Surface* Number8 = 0;
SDL_Surface* Number9 = 0;
SDL_Surface* Win_O = 0;
SDL_Surface* Win_B = 0;
SDL_Surface* PuntuacionX = 0;//puntuacion del jugador de abajo
SDL_Surface* PuntuacionY = 0;//puntuacion del jugador de arriba
SDL_Surface* GameOver = 0;

void dibujarTexto()
{
	
	


}
int LoadGameGraphics()
{
	GameOver = SDL_LoadBMP("game_over1.bmp");
    PaddleGraphic1 = SDL_LoadBMP("paddle_1.bmp");
    PaddleGraphic2 = SDL_LoadBMP("paddle_2.bmp");
    Number0 = SDL_LoadBMP("Number0.bmp");
    NumberSize_H = Number0->h;
    NumberSize_W = Number0->w;
    Number1 = SDL_LoadBMP("Number1.bmp");
    Number2 = SDL_LoadBMP("Number2.bmp");
    Number3 = SDL_LoadBMP("Number3.bmp");
    Number4 = SDL_LoadBMP("Number4.bmp");
    Number5 = SDL_LoadBMP("Number5.bmp");
    Number6 = SDL_LoadBMP("Number6.bmp");
    Number7 = SDL_LoadBMP("Number7.bmp");
    Number8 = SDL_LoadBMP("Number8.bmp");
    Number9 = SDL_LoadBMP("Number9.bmp");
    Win_O = SDL_LoadBMP("win_orange.bmp");
     Win_B = SDL_LoadBMP("win_blue.bmp");
    PuntuacionY = Number0;
    PuntuacionX = Number0;
    Fondo = SDL_LoadBMP("fondo.bmp");
    if (!PaddleGraphic1)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    PaddleSize_W = PaddleGraphic1->w;
    PaddleSize_H = PaddleGraphic1->h;

    BallGraphic = SDL_LoadBMP("ball.bmp");
    Life1 = SDL_LoadBMP("ball.bmp");
    Life2 = SDL_LoadBMP("ball.bmp");
    Life3 = SDL_LoadBMP("ball.bmp");
    if (!BallGraphic)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    BallSize_W = BallGraphic->w;
    BallSize_H = BallGraphic->h;

    return 0;
}

void FreeGameGraphics()
{
    SDL_FreeSurface(PaddleGraphic1);
    SDL_FreeSurface(BallGraphic);
}

void DrawGameGraphics(SDL_Surface * screen)
{
	if(puntos.X < 10 && puntos.Y<10){
    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_Rect dstrect;
    
    //dibujar fondo
    dstrect.x = (int)0;
    dstrect.y = (int)ScreenSize_H/2;

    // draw fondo bitmap
    SDL_BlitSurface(Fondo, 0, screen, &dstrect);
    
    
    dstrect.x = (int)Paddle2Position.X;
    dstrect.y = (int)Paddle2Position.Y;

    // draw paddle2 bitmap
    SDL_BlitSurface(PaddleGraphic2, 0, screen, &dstrect);
    
    dstrect.x = (int)PaddlePosition.X;
    dstrect.y = (int)PaddlePosition.Y;

    // draw paddle bitmap
    SDL_BlitSurface(PaddleGraphic1, 0, screen, &dstrect);

    dstrect.x = (int)BallPosition.X;
    dstrect.y = (int)BallPosition.Y;

    // draw ball bitmap
    SDL_BlitSurface(BallGraphic, 0, screen, &dstrect);
    
    // vida 1
    switch((int)puntos.X){
		case 0: PuntuacionX=Number0;break;
		case 1: PuntuacionX=Number1;break;
		case 2: PuntuacionX=Number2;break;
		case 3: PuntuacionX=Number3;break;
		case 4: PuntuacionX=Number4;break;
		case 5: PuntuacionX=Number5;break;
		case 6: PuntuacionX=Number6;break;
		case 7: PuntuacionX=Number7;break;
		case 8: PuntuacionX=Number8;break;
		case 9: PuntuacionX=Number9; SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_Rect dstrect;
  //dibujar la puntuacion de x
    dstrect.x = (ScreenSize_W + Win_B->w)/2;
    dstrect.y = (ScreenSize_H + Win_B->h)/2;

    // draw paddle bitmap
    SDL_BlitSurface(Win_O, 0, screen, &dstrect);

    // finally, update the screen :)
    SDL_Flip(screen);break;
		default: break;
	}
		
        switch((int)puntos.Y){
		case 0: PuntuacionY=Number0;break;
		case 1: PuntuacionY=Number1;break;
		case 2: PuntuacionY=Number2;break;
		case 3: PuntuacionY=Number3;break;
		case 4: PuntuacionY=Number4;break;
		case 5: PuntuacionY=Number5;break;
		case 6: PuntuacionY=Number6;break;
		case 7: PuntuacionY=Number7;break;
		case 8: PuntuacionY=Number8;break;
		case 9: PuntuacionY=Number9;  SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));


     SDL_Rect dstrect;
       dstrect.x = (ScreenSize_W + Win_B->w)/2;
    dstrect.y = (ScreenSize_H + Win_B->h)/2;

    // draw paddle bitmap
    SDL_BlitSurface(Win_B, 0, screen, &dstrect);
		default: break;
	}
	 //dibujar la puntuacion de Y
    dstrect.x = 0;
    dstrect.y = 0;

    // draw paddle bitmap
    SDL_BlitSurface(PuntuacionY, 0, screen, &dstrect);
	

    //dibujar la puntuacion de x
    dstrect.x = (ScreenSize_W - NumberSize_W);
    dstrect.y = (ScreenSize_H - NumberSize_H);;

    // draw paddle bitmap
    SDL_BlitSurface(PuntuacionX, 0, screen, &dstrect);
	
    SDL_Flip(screen);
}

}
