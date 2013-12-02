#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>
typedef struct
{
    SDL_Surface *Quitter;
    SDL_Surface *fond;

    SDL_Rect PositionQuitter;
    TTF_Font *police ;
} ComposantsAide;
void ComposantsPourAide(ComposantsAide *);
void BlitterComposantsAide(ComposantsAide*);
void LibererComposantsAide(ComposantsAide*);
void Aide();

