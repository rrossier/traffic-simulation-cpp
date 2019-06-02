/*
editeur.cpp
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "editeur.h"
#include "fichiers.h"

void editeur(SDL_Surface* ecran)
{

    SDL_Surface *plein = NULL, *voiture = NULL, *feuvert = NULL, *feurouge = NULL, *objectif= NULL, *carrefour= NULL;
    SDL_Rect position;
    SDL_Event event;

    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    int objetActuel = PLEIN, i = 0, j = 0;
    int**carte=new int*[NB_BLOCS_LARGEUR];
    for(int i=0;i<NB_BLOCS_LARGEUR;i++)
    {
        carte[i]=new int[NB_BLOCS_HAUTEUR];
    }
    // Chargement des objets et du niveau
    plein = IMG_Load("mur.jpg");
    voiture = IMG_Load("mario_bas.gif");
    feuvert = IMG_Load("feu_vert.jpg");
    feurouge = IMG_Load("feu_rouge.jpg");
    objectif = IMG_Load("objectif.gif");
    carrefour = IMG_Load("carrefour.jpg");

    if (!chargerNiveau(carte))
        exit(EXIT_FAILURE);

    // Boucle infinie de l'éditeur
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    // On met l'objet actuellement choisi (mur, caisse...) à l'endroit du clic
                    carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                    clicGaucheEnCours = 1; // On active un booléen pour retenir qu'un bouton est enfoncé
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) // Le clic droit sert à effacer
                {
                    carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC] = VIDE;
                    clicDroitEnCours = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP: // On désactive le booléen qui disait qu'un bouton était enfoncé
                if (event.button.button == SDL_BUTTON_LEFT)
                    clicGaucheEnCours = 0;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    clicDroitEnCours = 0;
                break;
            case SDL_MOUSEMOTION:
                if (clicGaucheEnCours) // Si on déplace la souris et que le bouton gauche de la souris est enfoncé
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
                }
                else if (clicDroitEnCours) // Pareil pour le bouton droit de la souris
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_s:
                        sauvegarderNiveau(carte);
                        break;
                    case SDLK_c:
                        chargerNiveau(carte);
                        break;
                    case SDLK_KP1:
                        objetActuel = PLEIN;
                        break;
                    case SDLK_KP2:
                        objetActuel = VOITURE;
                        break;
                    case SDLK_KP3:
                        objetActuel = FEUVERT;
                        break;
                    case SDLK_KP4:
                        objetActuel = FEUROUGE;
                        break;
                    case SDLK_KP5:
                        objetActuel = OBJECTIF;
                        break;
                    case SDLK_KP6:
                        objetActuel = CARREFOUR;
                        break;
                }
                break;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        // Placement des objets à l'écran
        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case PLEIN:
                        SDL_BlitSurface(plein, NULL, ecran, &position);
                        break;
                    case VOITURE:
                        SDL_BlitSurface(voiture, NULL, ecran, &position);
                        break;
                    case FEUVERT:
                        SDL_BlitSurface(feuvert, NULL, ecran, &position);
                        break;
                    case FEUROUGE:
                        SDL_BlitSurface(feurouge, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        break;
                    case CARREFOUR:
                        SDL_BlitSurface(carrefour, NULL, ecran, &position);
                        break;
                }
            }
        }

        // Mise à jour de l'écran
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(plein);
    SDL_FreeSurface(voiture);
    SDL_FreeSurface(feuvert);
    SDL_FreeSurface(feurouge);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(carrefour);
}

