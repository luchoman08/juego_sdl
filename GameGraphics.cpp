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
SDL_Surface* GameOver = 0;
int LoadGameGraphics()
{
	GameOver = SDL_LoadBMP("game_over1.bmp");
    PaddleGraphic1 = SDL_LoadBMP("paddle_1.bmp");
    PaddleGraphic1 = SDL_LoadBMP("paddle_2.bmp");
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
	if(vidas>0){
    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_Rect dstrect;
    dstrect.x = (int)PaddlePosition.X;
    dstrect.y = (int)PaddlePosition.Y;

    // draw paddle bitmap
    SDL_BlitSurface(PaddleGraphic1, 0, screen, &dstrect);

    dstrect.x = (int)BallPosition.X;
    dstrect.y = (int)BallPosition.Y;

    // draw ball bitmap
    SDL_BlitSurface(BallGraphic, 0, screen, &dstrect);
    
    // vida 1
	if(vidas > 0){
	dstrect.x = (int)20;
    dstrect.y = (int)20;
    SDL_BlitSurface(Life1, 0, screen, &dstrect);
	}
	if(vidas > 1){
    dstrect.x = (int)BallSize_H+25;
    dstrect.y = (int)20;
    SDL_BlitSurface(Life2, 0, screen, &dstrect);
	}
	if(vidas > 2){
    dstrect.x = (int)(2*BallSize_H+30);
    dstrect.y = (int)20;
    SDL_BlitSurface(Life3, 0, screen, &dstrect);
	}
    // finally, update the screen :)
    SDL_Flip(screen);
}
else{

    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_Rect dstrect;
    dstrect.x = (int)(ScreenSize_W /2) - GameOver->w /2 ;
    dstrect.y = (int)ScreenSize_H/2;

    // draw paddle bitmap
    SDL_BlitSurface(GameOver, 0, screen, &dstrect);

    // finally, update the screen :)
    SDL_Flip(screen);
}
}
