#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include"jeu1.h"
void Composants_Pour_FonctionPourJeu2(ComposantsFonctionPourJeu *Composants_Pour_FonctionPourJeu)
{
    Composants_Pour_FonctionPourJeu->police = TTF_OpenFont("PRISTINA.TTF", 25);
    TTF_SetFontStyle(Composants_Pour_FonctionPourJeu->police, TTF_STYLE_ITALIC);
    SDL_Color couleurNoire = {"#f", 0, "#a"};
    Composants_Pour_FonctionPourJeu->croix = SDL_LoadBMP("images/Croix.bmp");
    Composants_Pour_FonctionPourJeu->rond = SDL_LoadBMP("images/Rond.bmp");
    Composants_Pour_FonctionPourJeu->PointsCroix= SDL_LoadBMP( "images/petiteCroix.bmp");
    Composants_Pour_FonctionPourJeu->PointsRond = SDL_LoadBMP( "images/PetitRond.bmp");
    Composants_Pour_FonctionPourJeu->grille = SDL_LoadBMP ("images/6 colone.bmp");
    Composants_Pour_FonctionPourJeu->TextePoints= SDL_LoadBMP("images/Points.bmp");
    Composants_Pour_FonctionPourJeu->ImageMorpion[0]= SDL_LoadBMP( "images/morpionGrille.bmp" );
    Composants_Pour_FonctionPourJeu->ImageMorpion[1]= SDL_LoadBMP( "images/morpionGrille2.bmp");
    Composants_Pour_FonctionPourJeu->ImageMorpion[2]= SDL_LoadBMP( "images/morpionGrille3.bmp");
    Composants_Pour_FonctionPourJeu->ImageMorpion[2]= SDL_LoadBMP( "images/morpionGrille3.bmp");
    //Composants_Pour_FonctionPourJeu->img= SDL_LoadBMP( "images/play.bmp");
    Composants_Pour_FonctionPourJeu->Quitter= TTF_RenderText_Blended(Composants_Pour_FonctionPourJeu->police, "Retour au menu Principal", couleurNoire);

    Composants_Pour_FonctionPourJeu->positionImageMorpion.x = 900;
    Composants_Pour_FonctionPourJeu->positionImageMorpion.y = 0;
    Composants_Pour_FonctionPourJeu->positionImagePoints.x=30;
    Composants_Pour_FonctionPourJeu->positionImagePoints.y=550;
    Composants_Pour_FonctionPourJeu->position_Grille.x = 250;
    Composants_Pour_FonctionPourJeu->position_Grille.y = 30;
    Composants_Pour_FonctionPourJeu->positionPointsCroix.y=550;/*L'ordonnée des 2 images puisqu'on donne l'abcisse après!*/
    Composants_Pour_FonctionPourJeu->positionPointsRond.y=615;
    Composants_Pour_FonctionPourJeu->pos_Quitter.x=460;
    Composants_Pour_FonctionPourJeu->pos_Quitter.y=650;
   /* pos_img.x = 500;
    pos_img.y = 260;*/
}
void Blits2( int terrain[][6], int Variable_Pour_Image , int pointJoueur1, int pointJoueur2 ,ComposantsFonctionPourJeu* Charger)
{
    int i,j;
    SDL_FillRect(SDL_GetVideoSurface(), NULL, SDL_MapRGB(SDL_GetVideoSurface()->format, 255, 255, 255));
    SDL_BlitSurface(Charger->grille, NULL, SDL_GetVideoSurface(), &Charger->position_Grille);
    SDL_BlitSurface(Charger->TextePoints, NULL, SDL_GetVideoSurface(), &Charger->positionImagePoints);
    SDL_BlitSurface(Charger->ImageMorpion[0], NULL, SDL_GetVideoSurface(), &Charger->positionImageMorpion);
    SDL_BlitSurface(Charger->Quitter, NULL, SDL_GetVideoSurface(), &Charger->pos_Quitter);
    for (i = 0 ; i < 6 ; i++)
    {
        for (j = 0 ; j < 6 ; j++)
        {
            Charger->position.x = (i * 100)+250;
            Charger->position.y = (j * 80)+30;

            switch(terrain[i][j])
            {
            case VIDE:
                break;
            case CROIX:
                SDL_BlitSurface(Charger->croix, NULL, SDL_GetVideoSurface(), &Charger->position);
                break;
            case ROND:
                SDL_BlitSurface(Charger->rond, NULL, SDL_GetVideoSurface(), &Charger->position);
                break;
            }
        }
    }
    /*On met à jour et on blit les textes et l'image à gauche de la grille*/
    SDL_BlitSurface(Charger->TextePoints, NULL, SDL_GetVideoSurface(), &Charger->positionImagePoints);
    SDL_BlitSurface(Charger->ImageMorpion[Variable_Pour_Image], NULL, SDL_GetVideoSurface(), &Charger->positionImageMorpion);

    /*On place les images à 35 pixels de distance après avoir blitté les images (pour pouvoir blitter pas dessus)*/
    for(i=0; i<pointJoueur1; i++)
    {
        Charger->positionPointsCroix.x=(10+i*35)+240;
        SDL_BlitSurface(Charger->PointsCroix, NULL, SDL_GetVideoSurface(), &Charger->positionPointsCroix);
    }
    for(i=0; i<pointJoueur2; i++)
    {
        Charger->positionPointsRond.x=(10+i*35)+240;
        SDL_BlitSurface(Charger->PointsRond, NULL, SDL_GetVideoSurface(), &Charger->positionPointsRond);
    }
}
void evenement_Click2( SDL_Event event,Pions* TourJoueur,ComposantsFonctionPourJeu Charger,int terrain[][6],int*coups,SDL_Surface **Curseur,int*Variable_Pour_Image )
{
    if( event.button.button == SDL_BUTTON_LEFT && event.button.x<=850 && event.button.y<=520)
    {
        if (collision(event.button.x, event.button.y, Charger.position_Grille))
        {
            if( *TourJoueur == CROIX )
            {
                if (terrain[(event.button.x -250)/ 100][(event.button.y -30)/ 80]==VIDE)/*Si la case est vide*/
                {
                    Mix_PlayChannel(1, Mix_GetChunk(0) , 0);
                    terrain[(event.button.x -250)/ 100][(event.button.y -30)/ 80]= CROIX;/*on attribut Croix à la case*/
                    *TourJoueur = ROND;/*on change de joueur*/
                    (*coups)--;
                    SDL_FreeSurface(*Curseur);
                    *Curseur= SDL_LoadBMP("images/petitRond.bmp");
                }
            }
            else
            {
                if (terrain[(event.button.x -250)/ 100][(event.button.y -30)/ 80]==VIDE)/*Si la case est vide*/
                {
                    Mix_PlayChannel(1, Mix_GetChunk(0), 0);
                    terrain[(event.button.x -250)/ 100][(event.button.y -30)/ 80]= ROND;/*on attribut ROND à la case*/
                    *TourJoueur = CROIX;
                    (*coups)--;
                    SDL_FreeSurface(*Curseur);
                    *Curseur= SDL_LoadBMP("images/petiteCroix.bmp");
                }
            }
        }
        (*Variable_Pour_Image)++;/*l'anim change à chaque clic*/
        if (*Variable_Pour_Image==3)
        {
            *Variable_Pour_Image=0;
        }
    }
}
void libererJeu2(ComposantsFonctionPourJeu* Charger)
{
    int i;
    SDL_FreeSurface(Charger->croix);/* on libère le tout*/
    SDL_FreeSurface(Charger->rond);
    SDL_FreeSurface(Charger->PointsCroix);
    SDL_FreeSurface(Charger->PointsRond);
    SDL_FreeSurface(Charger->grille);
    SDL_FreeSurface(Charger->TextePoints);
    SDL_FreeSurface(Charger->Quitter);
    TTF_CloseFont(Charger->police);
    for (i=0; i<6; i++)
    {
        SDL_FreeSurface(Charger->ImageMorpion[i]);
    }
}
void Jeu2()
{
    SDL_Event event;
    SDL_Surface *Curseur=SDL_LoadBMP("images/petiteCroix.bmp");;
    SDL_Rect positionCurseur;

    int recommencer=1;/* Pour le grand do while*/
    int pointJoueur1=0, pointJoueur2=0;
    int gagnant;
    int VariablePourSon=0;
    int Bloquer_Affichage_Son=1;

    ComposantsFonctionPourJeu Charger;
    Composants_Pour_FonctionPourJeu2(&Charger);
    do
    {
        int terrain[6][6] = {{0}};/*On réinitialise les valeurs*/
        int continuer = 1;
        int coups =36;
        int Variable_Pour_Image=0;
        Pions TourJoueur = CROIX;/*Les croix Commencent*/
        /*Un premier blit pour une belle présentation*/
        Blits2(terrain, Variable_Pour_Image , pointJoueur1, pointJoueur2 ,&Charger);

        while (continuer && coups >0)
        {
            SDL_WaitEvent(&event);
            switch( event.type )
            {
            case SDL_MOUSEMOTION:
                Bloquer_Affichage_Son=1;
                /*if (collision(event.button.x,event.button.y, Charger.pos_Quitter ))
                {
                    SDL_FreeSurface(Curseur);
                }*/
                break;
            case SDL_QUIT:
                SDL_FreeSurface(Curseur);
                libererJeu2(&Charger);
                exit(0);
                break;
            case SDL_MOUSEBUTTONUP:
                evenement_Click2(event,&TourJoueur,Charger,terrain,&coups,&Curseur,&Variable_Pour_Image);
                if (collision(event.button.x,event.button.y, Charger.pos_Quitter ))
                {
                    continuer=0;
                    libererJeu1(&Charger);
                    Choix();
                }
                break;
            case SDL_KEYDOWN: /* Si appui d'une touche */
                switch (event.key.keysym.sym)
                {
                case SDLK_s:
                    Blits2(terrain, Variable_Pour_Image , pointJoueur1, pointJoueur2 ,&Charger);
                    ModifierSon (&VariablePourSon);
                    Bloquer_Affichage_Son=0;
                    break;
                case SDLK_ESCAPE:
                    continuer=0;
                    SDL_FreeSurface(Curseur);
                    libererJeu2(&Charger);
                    MenuPrincipal();
                    break;
                default:
                    break;
                }
                break;
            }
            if (Bloquer_Affichage_Son==1)
            {
                /*On vérifie si la partie est finie*/
                VerifierFinMatch2(terrain,&pointJoueur1,&pointJoueur2, &continuer , &gagnant );
                Blits2(terrain, Variable_Pour_Image , pointJoueur1, pointJoueur2 ,&Charger);
                /*après tout ça on blit le curseur*/
                positionCurseur.x = event.motion.x-(Curseur->w / 2);
                positionCurseur.y = event.motion.y-(Curseur->h / 2);
                SDL_BlitSurface(Curseur, NULL, SDL_GetVideoSurface(), &positionCurseur);
                SDL_Flip(SDL_GetVideoSurface());
            }
        }
        SDL_Delay(500);/*On patiente pour que l'utilisateur voie ou l'adversaire à joué*/
        FinMatch(&recommencer, &gagnant);/*Affichage gagné/ perdu/ MatchNull */
        SDL_Flip(SDL_GetVideoSurface());
        Curseur=SDL_LoadBMP("images/petiteCroix.bmp");
    }
    while (recommencer);
    SDL_FreeSurface(Curseur);
    libererJeu2(&Charger);
}
void VerifierFinMatch2(int terrain [][6],int *pointJoueur1,int *pointJoueur2 ,int *continuer, int *gagnant)
{
    int i,j,k,l,m,n;
    m=*pointJoueur1;
    n=*pointJoueur2;
     for (i=0;i<6;i++)
    {
        for(j=0;j<3;j++)
        {
            if((terrain [i][j]== CROIX && terrain [i][j+1]== CROIX && terrain [i][j+2]== CROIX && terrain [i][j+3]== CROIX )||
                (terrain [j][i]== CROIX && terrain [j+1][i]== CROIX && terrain [j+2][i]== CROIX && terrain [j+3][i]== CROIX ))
            {
              *pointJoueur1+=1;
              *continuer=0;
              *gagnant=Joueur1;
            }
        }
    }
    for (l=0;l<3;l++)
    {
        if  ((terrain [l][l]== CROIX && terrain [l+1][l+1]== CROIX && terrain [l+2][l+2]== CROIX && terrain [l+3][l+3]== CROIX )||
            (terrain [l][5-l]== CROIX && terrain [l+1][4-l]== CROIX && terrain [l+2][3-l]== CROIX && terrain [l+3][2-l]== CROIX ))
        {
          *pointJoueur1+=1;
          *continuer=0;
          *gagnant=Joueur1;
        }
    }
    for(k=0;k<2;k++)
    {
        if((terrain [k][k+1]== CROIX && terrain [k+1][k+2]== CROIX && terrain [k+2][k+3]== CROIX && terrain [k+3][k+4]== CROIX )||
            (terrain [k+1][k]== CROIX && terrain [k+2][k+1]== CROIX && terrain [k+3][k+2]== CROIX && terrain [k+4][k+3]== CROIX )||
            (terrain [k][4-k]== CROIX && terrain [k+1][3-k]== CROIX && terrain [k+2][2-k]== CROIX && terrain [k+3][1-k]== CROIX )||
            (terrain [k+1][5-k]== CROIX && terrain [k+2][4-k]== CROIX && terrain [k+3][3-k]== CROIX && terrain [k+4][2-k]== CROIX ))
        {
          *pointJoueur1+=1;
          *continuer=0;
          *gagnant=Joueur1;

        }
    }
    if((terrain [0][3]== CROIX && terrain [1][2]== CROIX && terrain [2][1]== CROIX && terrain [3][0]== CROIX )||
        (terrain [0][2]== CROIX && terrain [1][3]== CROIX && terrain [2][4]== CROIX && terrain [3][5]== CROIX )||
        (terrain [2][5]== CROIX && terrain [3][4]== CROIX && terrain [4][3]== CROIX && terrain [5][2]== CROIX )||
        (terrain [2][0]== CROIX && terrain [3][1]== CROIX && terrain [4][2]== CROIX && terrain [5][3]== CROIX ))
    {
          *pointJoueur1+=1;
          *continuer=0;
          *gagnant=Joueur1;

    }
    for (i=0;i<6;i++)
    {
        for(j=0;j<3;j++)
        {
            if((terrain [i][j]== ROND && terrain [i][j+1]== ROND && terrain [i][j+2]== ROND && terrain [i][j+3]== ROND )||
                (terrain [j][i]== ROND && terrain [j+1][i]== ROND && terrain [j+2][i]== ROND && terrain [j+3][i]== ROND ))
            {
                *pointJoueur2+=1;
                *continuer=0;
                *gagnant=Joueur2;
            }
        }
    }
    for (l=0;l<3;l++)
    {
        if  ((terrain [l][l]== ROND && terrain [l+1][l+1]== ROND && terrain [l+2][l+2]== ROND && terrain [l+3][l+3]== ROND )||
            (terrain [l][5-l]== ROND && terrain [l+1][4-l]== ROND && terrain [l+2][3-l]== ROND && terrain [l+3][2-l]== ROND ))
        {
            *pointJoueur2+=1;
            *continuer=0;
            *gagnant=Joueur2;
        }
    }
    for(k=0;k<2;k++)
    {
        if((terrain [k][k+1]== ROND && terrain [k+1][k+2]== ROND && terrain [k+2][k+3]== ROND && terrain [k+3][k+4]== ROND )||
            (terrain [k+1][k]== ROND && terrain [k+2][k+1]== ROND && terrain [k+3][k+2]== ROND && terrain [k+4][k+3]== ROND )||
            (terrain [k][4-k]== ROND && terrain [k+1][3-k]== ROND && terrain [k+2][2-k]== ROND && terrain [k+3][1-k]== ROND )||
            (terrain [k+1][5-k]== ROND && terrain [k+2][4-k]== ROND && terrain [k+3][3-k]== ROND && terrain [k+4][2-k]== ROND ))
        {
            *pointJoueur2+=1;
            *continuer=0;
            *gagnant=Joueur2;
        }
    }
        if((terrain [0][3]== ROND && terrain [1][2]== ROND && terrain [2][1]== ROND && terrain [3][0]== ROND )||
            (terrain [0][2]== ROND && terrain [1][3]== ROND && terrain [2][4]== ROND && terrain [3][5]== ROND )||
            (terrain [2][5]== ROND && terrain [3][4]== ROND && terrain [4][3]== ROND && terrain [5][2]== ROND )||
            (terrain [2][0]== ROND && terrain [3][1]== ROND && terrain [4][2]== ROND && terrain [5][3]== ROND ))
        {
            *pointJoueur2+=1;
            *continuer=0;
            *gagnant=Joueur2;
        }
        if ((*gagnant!=Joueur2)&&(*gagnant!=Joueur1))
        {
            *gagnant=MatchNull;
        }
        if (*pointJoueur1>m)
        *pointJoueur1=m+1;
        if (*pointJoueur2>n)
        *pointJoueur2=n+1;

}
