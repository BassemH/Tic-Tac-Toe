#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include"jeu1.h"
typedef struct
{
    SDL_Surface *texte;
    SDL_Surface *texteOui;
    SDL_Surface *texteNon ;
    SDL_Surface *fond;

    SDL_Rect positionTexte ;
    SDL_Rect positionTexteOui;
    SDL_Rect positionTexteNon ;

    Mix_Chunk *Gagne ;
    Mix_Chunk *huer ;
    TTF_Font *police ;
} ComposantsAffichage;
void ComposantsPourAffichage(ComposantsAffichage *ComposantsPourAffichage)
{
    ComposantsPourAffichage->police = TTF_OpenFont("police.ttf", 20);
    TTF_SetFontStyle(ComposantsPourAffichage->police, TTF_STYLE_ITALIC);
    SDL_Color couleurNoire = {0, 0, 0};
    ComposantsPourAffichage->texte = TTF_RenderText_Blended(ComposantsPourAffichage->police, "-------- Voulez vous Recommencer ? -------", couleurNoire);
    ComposantsPourAffichage->texteOui = TTF_RenderText_Blended(ComposantsPourAffichage->police, "OUI", couleurNoire);
    ComposantsPourAffichage->texteNon = TTF_RenderText_Blended(ComposantsPourAffichage->police, "NON", couleurNoire);
    ComposantsPourAffichage->Gagne = Mix_LoadWAV("musiques/gagne.wav");
    ComposantsPourAffichage->huer =  Mix_LoadWAV("musiques/huer.wav");
}
void BlitterComposantsPourAffichage(ComposantsAffichage* Charger)
{
    SDL_FillRect(SDL_GetVideoSurface(), NULL, SDL_MapRGB(SDL_GetVideoSurface()->format, 255, 255, 255));
    SDL_BlitSurface(Charger->fond, NULL, SDL_GetVideoSurface(), NULL);
    SDL_BlitSurface(Charger->texte, NULL, SDL_GetVideoSurface(), &Charger->positionTexte);
    SDL_BlitSurface(Charger->texteOui, NULL, SDL_GetVideoSurface(), &Charger->positionTexteOui);
    SDL_BlitSurface(Charger->texteNon, NULL, SDL_GetVideoSurface(), &Charger->positionTexteNon);
    SDL_Flip(SDL_GetVideoSurface());
}
void LibererComposantsPourAffichage(ComposantsAffichage* Charger)
{
    SDL_FreeSurface (Charger->texte);
    SDL_FreeSurface(Charger->texteOui);
    SDL_FreeSurface(Charger->texteNon);
    SDL_FreeSurface(Charger->fond);
    Mix_FreeChunk(Charger->Gagne);
    Mix_FreeChunk(Charger->huer);
    TTF_CloseFont(Charger->police);
}
void Coordonees_Images(ComposantsAffichage* Charger, int gagnant)
{
    if (gagnant== Joueur1 || gagnant== Joueur2)
    {
        Charger->positionTexte.x=350;
        Charger->positionTexte.y=100;
        Charger->positionTexteOui.x=500;
        Charger->positionTexteOui.y=150;
        Charger->positionTexteNon.x=500;
        Charger->positionTexteNon.y=200;
    }
    else if (gagnant==MatchNull)
    {
        Charger->positionTexte.x=400;
        Charger->positionTexte.y=100;
        Charger->positionTexteOui.x=550;
        Charger->positionTexteOui.y=150;
        Charger->positionTexteNon.x=550;
        Charger->positionTexteNon.y=200;
    }
}
void FinMatch( int *recommencer, int *gagnant )
{
    SDL_Event event;
    int VariablePourSon=0;
    ComposantsAffichage Charger;
    ComposantsPourAffichage(&Charger);
    char nomSon[40]="";
    int continuer=1;
    switch (*gagnant)
    {
        case Joueur1:
            Charger.fond = SDL_LoadBMP("images/winner_j1.bmp");
            Mix_PlayChannel(1, Charger.Gagne, 0);
            break;
        case Joueur2:
            Charger.fond = SDL_LoadBMP("images/winner_j2.bmp");
            Mix_PlayChannel(1, Charger.Gagne, 0);
            break;
        case MatchNull:
            Charger.fond = SDL_LoadBMP("images/egalite.bmp");
            Mix_PlayChannel(1, Charger.huer, 0);
            break;
    }
    Coordonees_Images(&Charger,*gagnant);
    BlitterComposantsPourAffichage(&Charger);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch( event.type )
        {
        case SDL_QUIT:
            continuer=0;
            LibererComposantsPourAffichage(&Charger);
            exit (0);
            break;
        case SDL_MOUSEBUTTONUP:
            if (collision(event.button.x, event.button.y, Charger.positionTexteOui))
            {
                continuer=0;
                LibererComposantsPourAffichage(&Charger);
                *recommencer=1;
            }
            else if (collision(event.button.x,event.button.y, Charger.positionTexteNon ))
            {
                continuer=0;
                LibererComposantsPourAffichage(&Charger);
                MenuPrincipal();
            }
        case SDL_KEYDOWN: /* Si appui d'une touche */
            switch (event.key.keysym.sym)
            {
            case SDLK_s:
                BlitterComposantsPourAffichage(&Charger);
                ModifierSon (&VariablePourSon);
                break;
            default:
                break;
            }
            break;
        }
    }
}



