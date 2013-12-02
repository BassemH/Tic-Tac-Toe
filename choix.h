#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>
typedef struct
{
    //SDL_Surface *nom;
    SDL_Surface *choix;
    SDL_Surface *jou1;
    SDL_Surface *jou2;
    SDL_Surface *jou3;
    SDL_Surface *button1;
    SDL_Surface *button2;
    SDL_Surface *button3;
    SDL_Surface *Quitter;
    SDL_Surface *fond;

    //SDL_Rect pos_nom;
    SDL_Rect pos_choix;
    SDL_Rect pos_jou1;
    SDL_Rect pos_jou2;
    SDL_Rect pos_jou3;
    SDL_Rect pos_button1;
    SDL_Rect pos_button2;
    SDL_Rect pos_button3;
    SDL_Rect pos_Quitter;
    TTF_Font *police ;
} ComposantsChoix;
void ComposantsPourChoix(ComposantsChoix *);
void BlitterComposantsChoix(ComposantsChoix*);
void LibererComposantsChoix(ComposantsChoix*);
void Choix();

