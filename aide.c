#include"aide.h"
void ComposantsPourAide(ComposantsAide *ComposantsPourAide)
{
    ComposantsPourAide->police = TTF_OpenFont("PRISTINA.TTF", 25);
    TTF_SetFontStyle(ComposantsPourAide->police, TTF_STYLE_ITALIC);
    SDL_Color couleurNoire = {"#f", 0, "#a"};
    ComposantsPourAide->Quitter= TTF_RenderText_Blended(ComposantsPourAide->police, "Retour au menu Principal", couleurNoire);
    ComposantsPourAide->fond = SDL_LoadBMP("images/Morpion_aide.bmp");

    ComposantsPourAide->PositionQuitter.x=470;
    ComposantsPourAide->PositionQuitter.y=650;
}
void BlitterComposantsAide(ComposantsAide* Charger)
{
    SDL_BlitSurface(Charger->fond, NULL, SDL_GetVideoSurface(), NULL);
    SDL_BlitSurface(Charger->Quitter, NULL, SDL_GetVideoSurface(), &Charger->PositionQuitter);
    SDL_Flip(SDL_GetVideoSurface());
}
void LibererComposantsAide(ComposantsAide* Charger)
{
    SDL_FreeSurface(Charger->Quitter);
    SDL_FreeSurface(Charger->fond);
    TTF_CloseFont(Charger->police);
}
void Aide()
{
    SDL_Event event;
    int continuer=1;
    ComposantsAide Charger;
    ComposantsPourAide(&Charger);
    BlitterComposantsAide(&Charger);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch( event.type )
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_MOUSEBUTTONUP:

            if (collision(event.button.x,event.button.y, Charger.PositionQuitter ))
            {
                continuer=0;
                LibererComposantsAide(&Charger);
                MenuPrincipal();
            }
            break;
        case SDL_KEYDOWN: /* Si appui d'une touche */
            switch (event.key.keysym.sym)
            {
            case SDLK_s:
                BlitterComposantsOptions(&Charger);
                break;
            default:
                break;
            }
        }
    }
}

