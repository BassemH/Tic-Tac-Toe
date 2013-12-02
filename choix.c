#include"choix.h"
void ComposantsPourChoix(ComposantsChoix *ComposantsPourChoix)
{
    ComposantsPourChoix->police = TTF_OpenFont("PRISTINA.TTF", 30);
    TTF_SetFontStyle(ComposantsPourChoix->police, TTF_STYLE_ITALIC);
    SDL_Color couleurNoire = {"#f", 0, "#a"};
    ComposantsPourChoix->button1 = SDL_LoadBMP("images/play.bmp");
    ComposantsPourChoix->button2 = SDL_LoadBMP("images/play.bmp");
    ComposantsPourChoix->button3 = SDL_LoadBMP("images/play.bmp");
   // ComposantsPourChoix->nom = TTF_RenderText_Blended(ComposantsPourChoix->police, "Saisir Votre Nom :", couleurNoire);
    ComposantsPourChoix->choix = TTF_RenderText_Blended(ComposantsPourChoix->police, "Choisir le niveau du jeu", couleurNoire);
    ComposantsPourChoix->jou1 = TTF_RenderText_Blended(ComposantsPourChoix->police, "---- facile ----", couleurNoire);
    ComposantsPourChoix->jou2 = TTF_RenderText_Blended(ComposantsPourChoix->police, "---- moyen ----", couleurNoire);
    ComposantsPourChoix->jou3 = TTF_RenderText_Blended(ComposantsPourChoix->police, "---- difficile ----", couleurNoire);
    ComposantsPourChoix->Quitter= TTF_RenderText_Blended(ComposantsPourChoix->police, "Retour au menu Principal", couleurNoire);
    ComposantsPourChoix->fond = SDL_LoadBMP("images/Morpion Options.bmp");


    /*ComposantsPourChoix->pos_nom.x=30;
    ComposantsPourChoix->pos_nom.y=50;*/
    ComposantsPourChoix->pos_choix.x=450;
    ComposantsPourChoix->pos_choix.y=80;
    ComposantsPourChoix->pos_button1.x = 70;
    ComposantsPourChoix->pos_button1.y = 150;
    ComposantsPourChoix->pos_button2.x = 440;
    ComposantsPourChoix->pos_button2.y = 150;
    ComposantsPourChoix->pos_button3.x = 800;
    ComposantsPourChoix->pos_button3.y = 150;
    ComposantsPourChoix->pos_jou1.x=120;
    ComposantsPourChoix->pos_jou1.y=160;
    ComposantsPourChoix->pos_jou2.x=485;
    ComposantsPourChoix->pos_jou2.y=160;
    ComposantsPourChoix->pos_jou3.x=835;
    ComposantsPourChoix->pos_jou3.y=160;
    ComposantsPourChoix->pos_Quitter.x=420;
    ComposantsPourChoix->pos_Quitter.y=650;
}
void BlitterComposantsChoix(ComposantsChoix* Charger)
{
    SDL_BlitSurface(Charger->fond, NULL, SDL_GetVideoSurface(), NULL);
    //SDL_BlitSurface(Charger->nom, NULL, SDL_GetVideoSurface(), &Charger->pos_nom);
    SDL_BlitSurface(Charger->choix, NULL, SDL_GetVideoSurface(), &Charger->pos_choix);
    SDL_BlitSurface(Charger->button1, NULL,SDL_GetVideoSurface(), &Charger->pos_button1);
    SDL_BlitSurface(Charger->button2, NULL,SDL_GetVideoSurface(), &Charger->pos_button2);
    SDL_BlitSurface(Charger->button3, NULL,SDL_GetVideoSurface(), &Charger->pos_button3);
    SDL_BlitSurface(Charger->jou1, NULL, SDL_GetVideoSurface(), &Charger->pos_jou1);
    SDL_BlitSurface(Charger->jou2, NULL, SDL_GetVideoSurface(), &Charger->pos_jou2);
    SDL_BlitSurface(Charger->jou3, NULL, SDL_GetVideoSurface(), &Charger->pos_jou3);
    SDL_BlitSurface(Charger->Quitter, NULL, SDL_GetVideoSurface(), &Charger->pos_Quitter);
    SDL_Flip(SDL_GetVideoSurface());
}
void LibererComposantsChoix(ComposantsChoix* Charger)
{
    //SDL_FreeSurface (Charger->nom);
    SDL_FreeSurface (Charger->choix);
    SDL_FreeSurface (Charger->jou1);
    SDL_FreeSurface (Charger->jou2);
    SDL_FreeSurface (Charger->jou3);
    SDL_FreeSurface(Charger->button1);
    SDL_FreeSurface(Charger->button2);
    SDL_FreeSurface(Charger->button3);
    SDL_FreeSurface(Charger->Quitter);
    SDL_FreeSurface(Charger->fond);
    TTF_CloseFont(Charger->police);
}
void Choix()
{
    SDL_Event event;
    int continuer=1;
    ComposantsChoix Charger;
    ComposantsPourChoix(&Charger);
    BlitterComposantsChoix(&Charger);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch( event.type )
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_MOUSEBUTTONUP:

            /*if (collision(event.button.x,event.button.y, Charger.pos_nom ))
            {
                continuer=0;
                LibererComposantsChoix(&Charger);

            }
            else */if (collision(event.button.x,event.button.y, Charger.pos_choix ))
            {
                continuer=0;
                LibererComposantsChoix(&Charger);
                MenuPrincipal();
            }
            else if (collision(event.button.x,event.button.y, Charger.pos_jou1 )||collision(event.button.x,event.button.y, Charger.pos_button1))
            {
                continuer=0;
                LibererComposantsChoix(&Charger);
                Jeu1();
            }
            else if (collision(event.button.x,event.button.y, Charger.pos_jou2 )||collision(event.button.x,event.button.y, Charger.pos_button2))
            {
                continuer=0;
                LibererComposantsChoix(&Charger);
                Jeu2();
            }
            else if (collision(event.button.x,event.button.y, Charger.pos_jou3 )||collision(event.button.x,event.button.y, Charger.pos_button3))
            {
                continuer=0;
                LibererComposantsChoix(&Charger);
                Jeu3();
            }
            else if (collision(event.button.x,event.button.y, Charger.pos_Quitter ))
            {
                continuer=0;
                LibererComposantsChoix(&Charger);
                MenuPrincipal();
            }
            break;
        case SDL_KEYDOWN: /* Si appui d'une touche */
            switch (event.key.keysym.sym)
            {
            case SDLK_s:
                BlitterComposantsChoix(&Charger);
                break;
            default:
                break;
            }
        }
    }
}
