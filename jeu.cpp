/*
jeu.cpp
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>

#include "constantes.h"
#include "jeu.h"
#include "fichiers.h"

using namespace std;

Voiture::Voiture()
{
    int coordonnees_depart[4][5][2]={{{10,0},{24,0},{38,0},{52,0},{66,0}},{{69,10},{69,24},{69,38},{69,52},{69,66}},{{13,69},{27,69},{41,69},{55,69},{69,69}},{{0,13},{0,27},{0,41},{0,55},{0,69}}};
    int coordonnees_objectif[4][5][2]={{{10,69},{24,69},{38,69},{52,69},{66,69}},{{0,10},{0,24},{0,38},{0,52},{0,66}},{{13,0},{27,0},{41,0},{55,0},{69,0}},{{69,13},{69,27},{69,41},{69,55},{69,69}}};

    int sens_depart=rand() % 4; //entre 1 et 4 mais 0 et 3 en réalité, donc pas de +1.
    int pos_depart=rand() % 5; //là aussi entre 0 et 4.
    int pos_objectif=rand() % 5; //là aussi entre 0 et 4.
    int vit=8 + rand()%5;//vitesse entre 8 et 12.
    //coordonnees[sens_depart][pos_depart][0]
    //coordonnees[sens_depart][pos_depart][0]
    m_temps_depart=SDL_GetTicks();
    m_temps_attente=0;
    m_temps_buffer=0;
    m_objectif_atteint=false;
    m_numero=0;
    m_pos_x=coordonnees_depart[sens_depart][pos_depart][0];
    m_pos_y=coordonnees_depart[sens_depart][pos_depart][1];
    m_vitesse=8;
    m_sens_deplacement=sens_depart;
    m_voie_deplacement=0;
    for(int i=0;i<4;i++)
    m_vue[i]=NULL;

    for(int i=0;i<10;i++)
    m_memoire[i]=7;

    m_position_memoire=0;

    m_vue[BAS] = IMG_Load("mario_bas.gif");
    m_vue[GAUCHE] = IMG_Load("mario_gauche.gif");
    m_vue[HAUT] = IMG_Load("mario_haut.gif");
    m_vue[DROITE] = IMG_Load("mario_droite.gif");
    m_vue_actuelle=NULL;
    switch(sens_depart)
    {
        case 0:
        m_vue_actuelle=m_vue[BAS];
        break;

        case 1:
        m_vue_actuelle=m_vue[GAUCHE];
        break;

        case 2:
        m_vue_actuelle=m_vue[HAUT];
        break;

        case 3:
        m_vue_actuelle=m_vue[DROITE];
        break;
    }
    //SDL_Rect m_position, m_positionVoiture, m_positionObjectif;
    m_positionVoiture.x = m_pos_x;
    m_positionVoiture.y = m_pos_y;
    m_positionObjectif.x = coordonnees_objectif[sens_depart][pos_objectif][0];
    m_positionObjectif.y = coordonnees_objectif[sens_depart][pos_objectif][1];
    m_position.x = m_positionVoiture.x * TAILLE_BLOC;
    m_position.y = m_positionVoiture.y * TAILLE_BLOC;
}

/*Voiture::~Voiture()
{
//delete [] m_vue;
//delete m_vue_actuelle;
}*/

/*
Voiture::Voiture(int pos_x, int pos_y, int direction) : m_pos_x(pos_x), m_pos_y(pos_y), m_sens_deplacement(direction)
{
    int coordonnees_depart[4][5][2]={{{10,0},{24,0},{38,0},{52,0},{66,0}},{{69,10},{69,24},{69,38},{69,52},{69,66}},{{13,69},{27,69},{41,69},{55,69},{69,69}},{{0,13},{0,27},{0,41},{0,55},{0,69}}};
    int coordonnees_objectif[4][5][2]={{{10,69},{24,69},{38,69},{52,69},{66,69}},{{0,10},{0,24},{0,38},{0,52},{0,66}},{{13,0},{27,0},{41,0},{55,0},{69,0}},{{69,13},{69,27},{69,41},{69,55},{69,69}}};

    //int sens_depart=rand() % 4; //entre 1 et 4 mais 0 et 3 en réalité, donc pas de +1.
    //int pos_depart=rand() % 5; //là aussi entre 0 et 4.
    int pos_objectif=rand() % 5; //là aussi entre 0 et 4.
    int vit=8 + rand()%5;//vitesse entre 8 et 12.
    //coordonnees[sens_depart][pos_depart][0]
    //coordonnees[sens_depart][pos_depart][0]
    m_temps_depart=SDL_GetTicks();
    m_numero=0;
    //m_pos_x=coordonnees_depart[sens_depart][pos_depart][0];
    //m_pos_y=coordonnees_depart[sens_depart][pos_depart][1];
    m_vitesse=8;
    //m_sens_deplacement=sens_depart;
    m_voie_deplacement=0;
    for(int i=0;i<4;i++)
    m_vue[i]=NULL;

    for(int i=0;i<10;i++)
    m_memoire[i]=7;

    m_position_memoire=0;

    m_vue[BAS] = IMG_Load("mario_bas.gif");
    m_vue[GAUCHE] = IMG_Load("mario_gauche.gif");
    m_vue[HAUT] = IMG_Load("mario_haut.gif");
    m_vue[DROITE] = IMG_Load("mario_droite.gif");
    m_vue_actuelle=NULL;
    switch(m_sens_deplacement)
    {
        case 0:
        m_vue_actuelle=m_vue[BAS];
        break;

        case 1:
        m_vue_actuelle=m_vue[GAUCHE];
        break;

        case 2:
        m_vue_actuelle=m_vue[HAUT];
        break;

        case 3:
        m_vue_actuelle=m_vue[DROITE];
        break;
    }
    //SDL_Rect m_position, m_positionVoiture, m_positionObjectif;
    m_positionVoiture.x = m_pos_x;
    m_positionVoiture.y = m_pos_y;
    m_positionObjectif.x = coordonnees_objectif[m_sens_deplacement][pos_objectif][0];
    m_positionObjectif.y = coordonnees_objectif[m_sens_deplacement][pos_objectif][1];
    m_position.x = m_positionVoiture.x * TAILLE_BLOC;
    m_position.y = m_positionVoiture.y * TAILLE_BLOC;
}
*/

int Voiture::getNumber() const
{
    return m_numero;
}

int Voiture::getpos_x() const
{
    return m_positionVoiture.x;
}

int Voiture::getpos_y() const
{
    return m_positionVoiture.y;
}

/*
void Voiture::test_feu(int** carte)
{
    SDL_Event event;
    if (carte[m_positionVoiture.x][m_positionVoiture.y] == FEUROUGE) // S'il y a un feu rouge, on arrête
    {
        while(1)
        {
            SDL_WaitEvent(&event);
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                break;
            }
        }
    }
}
*/

void Voiture::blitage(SDL_Surface* ecran)
{
    m_position.x=m_positionVoiture.x * TAILLE_BLOC;
    m_position.y=m_positionVoiture.y * TAILLE_BLOC;

    SDL_BlitSurface(m_vue_actuelle, NULL, ecran, &m_position);
}

void Voiture::liberation()
{
    for (int i = 0 ; i < 4 ; i++)
    {
        SDL_FreeSurface(m_vue[i]);
    }
}

void Voiture::test_trajectoire(int** carte, int** carte2, SDL_Surface* ecran)
{
    /*
    Note:
        sens de déplacement:
        0   bas
        1   gauche
        2   haut
        3   droite

        il y a quatre tests pour décider de la direction à prendre
        si on est au vert on prend la décision en fonction des positions de la voiture et de son objectif
        si on est au feu rouge on ne fait rien, on attend
        si on est dans une rue (pas dans un carrefour!) on continue à se déplacer normalement
        si on est dans un carrefour (après être passé par un feu vert et avant d'arriver dans une rue)
            on utilise le tableau m_memoire pour se rappeler la décision prise et les déplacements à faire
            en conséquence.
            cf premier test pour explication de l'utilisation du tableau m_memoire

        à chaque feu les voitures tournant à gauche seront bien sur la voie de dépassement
        alors que celles allant tout droit ou à droite seront sur la voie normale
        la position sur telle ou telle voie est gérée un feu à l'avance:
        en effet le test est fait pour prévoir à l'avance le déplacement de la voiture si elle doit
        tourner à gauche.
    */

    if(carte[m_positionVoiture.x][m_positionVoiture.y]== FEUVERT)
    {
        int temps=SDL_GetTicks();
        m_temps_attente+=temps-m_temps_buffer;
        if(m_sens_deplacement==0)
        {//déplacement vers le bas
            if((m_positionObjectif.y-m_positionVoiture.y)<=4)
            {
                if(m_positionVoiture.x>m_positionObjectif.x)
                {
                    //tourner à gauche sur l'écran
                    m_vue_actuelle = m_vue[BAS];
                    deplacer(carte, carte2, BAS, ecran);//*1
                    /*
                    on ne peut faire qu'un seul déplacement à la fois
                    à cause du blitage qui n'apparait qu'après la boucle while
                    on doit donc gérer un système de mémoire pour connaitre la destination
                    par rapport aux décisions prises dans le passé.
                    pour ce faire on va utiliser un tableau qui lors de la prise de décision
                    enregistre les futurs déplacements,
                    à chaque déplacement la première cellule du tableau change
                    pour laisser la place à la deuxième cellule contenant le prochain déplacement
                    */
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=1;
                    m_memoire[1]=7;
                    //ici 7 jouera le role de délimiteur de fin à la manière de eof pour un fichier
                }
                else if(m_positionVoiture.x<m_positionObjectif.x)
                {
                    //tourner à droite
                    m_vue_actuelle = m_vue[BAS];
                    deplacer(carte, carte2, BAS, ecran);//*4
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=0;
                    m_memoire[1]=0;
                    m_memoire[2]=0;
                    m_memoire[3]=3;
                    m_memoire[4]=3;
                    m_memoire[5]=3;
                    m_memoire[6]=7;
                    /*
                    m_vue_actuelle = m_vue[DROITE];
                    deplacer(carte, carte2, DROITE, ecran);//*3
                    m_sens_deplacement=3;
                    */
                }
                else //les coords x sont égales
                {
                    //rester dans la voie, continuer tout droit
                    m_vue_actuelle = m_vue[BAS];
                    deplacer(carte, carte2, BAS, ecran);//*4
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=0;
                    m_memoire[1]=0;
                    m_memoire[2]=0;
                    m_memoire[3]=0;
                    m_memoire[4]=7;
                }
            }
            else if((m_positionObjectif.y-m_positionVoiture.y)<=18)
            {
                if(m_positionVoiture.x>=m_positionObjectif.x)
                {
                    //continuer tout droit
                    m_vue_actuelle = m_vue[BAS];
                    deplacer(carte, carte2, BAS, ecran);//*5
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=0;
                    m_memoire[1]=0;
                    m_memoire[2]=0;
                    m_memoire[3]=0;
                    m_memoire[4]=7;
                }
                else
                {
                    //aller dans la voie de dépassement
                    m_vue_actuelle = m_vue[BAS];
                    deplacer(carte, carte2, BAS, ecran);//*5
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=0;
                    m_memoire[1]=0;
                    m_memoire[2]=0;
                    m_memoire[3]=0;
                    m_memoire[4]=3;
                    m_memoire[5]=0;
                    m_memoire[6]=7;
                    /*
                    m_vue_actuelle = m_vue[DROITE];
                    deplacer(carte, carte2, DROITE, ecran);
                    m_vue_actuelle = m_vue[BAS];
                    deplacer(carte, carte2, BAS, ecran);
                    */
                }
            }
            else
            {
                //rester dans la voie, continuer tout droit
                m_vue_actuelle = m_vue[BAS];
                deplacer(carte, carte2, BAS, ecran);//*4
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=0;
                    m_memoire[1]=0;
                    m_memoire[2]=0;
                    m_memoire[3]=0;
                    m_memoire[4]=7;
            }
        }
        if(m_sens_deplacement==2)//haut
        {
            if((m_positionVoiture.y-m_positionObjectif.y)<=14)
            {
                if(m_positionVoiture.x<m_positionObjectif.x)
                {
                    //tourner à droite sur l'écran
                    m_vue_actuelle = m_vue[HAUT];
                    deplacer(carte, carte2, HAUT, ecran);//*1
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=3;
                    m_memoire[1]=7;
                }
                else if(m_positionVoiture.x>m_positionObjectif.x)
                {
                    //tourner à gauche
                    m_vue_actuelle = m_vue[HAUT];
                    deplacer(carte, carte2, HAUT, ecran);//*4
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=2;
                    m_memoire[1]=2;
                    m_memoire[2]=2;
                    m_memoire[3]=1;
                    m_memoire[4]=1;
                    m_memoire[5]=1;
                    m_memoire[6]=7;
                }
                else//coords x égales
                {
                    //continuer tout droit
                    m_vue_actuelle = m_vue[HAUT];
                    deplacer(carte, carte2, HAUT, ecran);//*5
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=2;
                    m_memoire[1]=2;
                    m_memoire[2]=2;
                    m_memoire[3]=2;
                    m_memoire[4]=7;
                }
            }
            else if((m_positionVoiture.y-m_positionObjectif.y)<=28)
            {
                if(m_positionVoiture.x<=m_positionObjectif.x)
                {
                    //continuer tout droit
                    m_vue_actuelle = m_vue[HAUT];
                    deplacer(carte, carte2, HAUT, ecran);//*5
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=2;
                    m_memoire[1]=2;
                    m_memoire[2]=2;
                    m_memoire[3]=2;
                    m_memoire[4]=7;
                }
                else
                {
                    //aller dans la voie de dépassement
                    m_vue_actuelle = m_vue[HAUT];
                    deplacer(carte, carte2, HAUT, ecran);//*5
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=2;
                    m_memoire[1]=2;
                    m_memoire[2]=2;
                    m_memoire[3]=2;
                    m_memoire[4]=1;
                    m_memoire[5]=2;
                    m_memoire[6]=7;
                }
            }
            else
            {
                //rester dans la voie, continuer tout droit
                m_vue_actuelle = m_vue[HAUT];
                deplacer(carte, carte2, HAUT, ecran);//*4
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=2;
                    m_memoire[1]=2;
                    m_memoire[2]=2;
                    m_memoire[3]=2;
                    m_memoire[4]=7;
            }
        }
        if(m_sens_deplacement==1)//gauche
        {
            if((m_positionVoiture.x-m_positionObjectif.x)<=14)
            {
                if(m_positionVoiture.y<m_positionObjectif.y)
                {
                    //tourner en bas sur l'écran
                    m_vue_actuelle = m_vue[GAUCHE];
                    deplacer(carte, carte2, GAUCHE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=1;
                    m_memoire[1]=1;
                    m_memoire[2]=1;
                    m_memoire[3]=0;
                    m_memoire[4]=0;
                    m_memoire[5]=0;
                    m_memoire[6]=0;//vient d'être rajouté
                    m_memoire[7]=7;
                }
                else if(m_positionVoiture.y>m_positionObjectif.y)
                {
                    //tourner en haut
                    m_vue_actuelle = m_vue[GAUCHE];
                    deplacer(carte, carte2, GAUCHE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=2;
                    m_memoire[1]=7;
                }
                else
                {
                    //reste dans la voie
                    m_vue_actuelle = m_vue[GAUCHE];
                    deplacer(carte, carte2, GAUCHE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=1;
                    m_memoire[1]=1;
                    m_memoire[2]=1;
                    m_memoire[3]=1;
                    m_memoire[4]=7;
                }
            }
            else if((m_positionVoiture.x-m_positionObjectif.x)<=28)
            {
                if(m_positionVoiture.y<m_positionObjectif.y)
                {
                    //se mettre dans la voie de dépassement
                    m_vue_actuelle = m_vue[GAUCHE];
                    deplacer(carte, carte2, GAUCHE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=1;
                    m_memoire[1]=1;
                    m_memoire[2]=1;
                    m_memoire[3]=1;
                    m_memoire[4]=0;
                    m_memoire[5]=1;
                    m_memoire[6]=7;
                }
                else
                {
                    //reste dans la voie
                    m_vue_actuelle = m_vue[GAUCHE];
                    deplacer(carte, carte2, GAUCHE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=1;
                    m_memoire[1]=1;
                    m_memoire[2]=1;
                    m_memoire[3]=1;
                    m_memoire[4]=7;
                }
            }
            else
            {
                //on traverse le carrefour
                m_vue_actuelle = m_vue[GAUCHE];
                deplacer(carte, carte2, GAUCHE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=1;
                    m_memoire[1]=1;
                    m_memoire[2]=1;
                    m_memoire[3]=1;
                    m_memoire[4]=7;
            }
        }
        if(m_sens_deplacement==3)//droite
        {
            if((m_positionObjectif.x-m_positionVoiture.x)<=4)
            {
                if(m_positionVoiture.y<m_positionObjectif.y)
                {
                    //tourner en bas sur l'écran
                    m_vue_actuelle = m_vue[DROITE];
                    deplacer(carte, carte2, DROITE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=0;
                    m_memoire[1]=7;
                }
                else if(m_positionVoiture.y>m_positionObjectif.y)
                {
                    //tourner en haut
                    m_vue_actuelle = m_vue[DROITE];
                    deplacer(carte, carte2, DROITE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=3;
                    m_memoire[1]=3;
                    m_memoire[2]=3;
                    m_memoire[3]=2;
                    m_memoire[4]=2;
                    m_memoire[5]=2;
                    m_memoire[6]=7;
                }
                else
                {
                    //reste dans la voie
                    m_vue_actuelle = m_vue[DROITE];
                    deplacer(carte, carte2, DROITE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=3;
                    m_memoire[1]=3;
                    m_memoire[2]=3;
                    m_memoire[3]=3;
                    m_memoire[4]=7;
                }
            }
            else if((m_positionObjectif.x-m_positionVoiture.x)<=18)
            {
                if(m_positionVoiture.y<m_positionObjectif.y)
                {
                    //se mettre dans la voie de dépassement
                    m_vue_actuelle = m_vue[DROITE];
                    deplacer(carte, carte2, DROITE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=3;
                    m_memoire[1]=3;
                    m_memoire[2]=3;
                    m_memoire[3]=3;
                    m_memoire[4]=2;
                    m_memoire[5]=3;
                    m_memoire[6]=7;
                }
                else
                {
                    //reste dans la voie
                    m_vue_actuelle = m_vue[DROITE];
                    deplacer(carte, carte2, DROITE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=3;
                    m_memoire[1]=3;
                    m_memoire[2]=3;
                    m_memoire[3]=3;
                    m_memoire[4]=7;
                }
            }
            else
            {
                //on traverse le carrefour
                m_vue_actuelle = m_vue[DROITE];
                deplacer(carte, carte2, DROITE, ecran);
                    for(int i=0;i<10;i++)
                    m_memoire[i]=7;

                    m_position_memoire=0;

                    m_memoire[0]=3;
                    m_memoire[1]=3;
                    m_memoire[2]=3;
                    m_memoire[3]=3;
                    m_memoire[4]=7;
            }
        }
    }
    else if(carte[m_positionVoiture.x][m_positionVoiture.y]== FEUROUGE)
    {
        m_temps_buffer=SDL_GetTicks();
    }
    else
    {
        if(m_memoire[m_position_memoire]==7)
        {
            for(int i=0;i<10;i++)
                m_memoire[i]=7;

            m_position_memoire=0;
            switch(m_sens_deplacement)
            {
                case 0:
                m_vue_actuelle = m_vue[BAS];
                deplacer(carte, carte2, BAS, ecran);//*10
                break;

                case 1:
                m_vue_actuelle = m_vue[GAUCHE];
                deplacer(carte, carte2, GAUCHE, ecran);//*10
                break;

                case 2:
                m_vue_actuelle = m_vue[HAUT];
                deplacer(carte, carte2, HAUT, ecran);//*10
                break;

                case 3:
                m_vue_actuelle = m_vue[DROITE];
                deplacer(carte, carte2, DROITE, ecran);//*10
                break;

                default:
                break;
            }

            m_position_memoire=0;//il faut remettre à zéro le compteur pour le prochain carrefour
        }
        else
        {
            switch(m_memoire[m_position_memoire])
            {
                case 0:
                m_vue_actuelle = m_vue[BAS];
                deplacer(carte, carte2, BAS, ecran);//*10
                m_sens_deplacement=0;
                m_position_memoire++;
                break;

                case 1:
                m_vue_actuelle = m_vue[GAUCHE];
                deplacer(carte, carte2, GAUCHE, ecran);//*10
                m_sens_deplacement=1;
                m_position_memoire++;
                break;

                case 2:
                m_vue_actuelle = m_vue[HAUT];
                deplacer(carte, carte2, HAUT, ecran);//*10
                m_sens_deplacement=2;
                m_position_memoire++;
                break;

                case 3:
                m_vue_actuelle = m_vue[DROITE];
                deplacer(carte, carte2, DROITE, ecran);//*10
                m_sens_deplacement=3;
                m_position_memoire++;
                break;

                default:
                break;
            }
        }
    }
}

void Voiture::retrouver_positions()
{
    for (int i = 0 ; i < NB_TOTAL_VOITURES ; i++)
    {
        m_position.x = m_position.x * TAILLE_BLOC;
        m_position.y = m_position.y * TAILLE_BLOC;
        //SDL_BlitSurface(marioActuel, NULL, ecran, &m_position);
    }
}

/*
void Voiture::test_collision()
{

}
*/

int Voiture::test_objectif(int** carte2, SDL_Surface *ecran)
{
    if((m_positionVoiture.x==m_positionObjectif.x)&&(m_positionVoiture.y==m_positionObjectif.y))
    {
        if(!m_objectif_atteint)
        {
            carte2[m_positionVoiture.x][m_positionVoiture.y]=VIDE;
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
            FILE * fichier=NULL;
            fichier=fopen("temps.txt","a");
            int temps_final=0;
            temps_final=SDL_GetTicks();
            int temps_ecoule=temps_final-m_temps_depart;
            //fprintf(fichier,"%d;%d\n",temps_ecoule,m_temps_attente);
            fprintf(fichier,"%d;%d;%d;%d;%d\n",m_pos_x,m_pos_y,m_positionObjectif.x,m_positionObjectif.y,temps_ecoule);
            fclose(fichier);
            m_objectif_atteint=true;
            //effacemment écran à cet endroit

            /*
            SDL_Surface *rectangle = NULL;
            rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 10, 32, 0, 0, 0, 0); // Allocation de la surface
            SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); // Remplissage de la surface avec du blanc
            SDL_BlitSurface(rectangle, NULL, ecran, &m_positionVoiture); // Collage de la surface sur l'écran

            SDL_Flip(ecran); // Mise à jour de l'écran

            SDL_FreeSurface(rectangle);
            */
            return 1;

        }
    }
    return 0;
}

/*
int***** enregistrement_feux()
{
    //j ligne i colonne, inversé par rapport à carte

    return feux;
}
*/
int *processus_poisson(double lambda, int nombre)
{
    if(lambda!=0)
    {
        srand(time(NULL));
        int * tableau= new int[nombre];
        for(int i=0;i<nombre;i++)
        {
            tableau[i]=(-1/lambda)*log(1-(rand()/(double)RAND_MAX))*1000;
        }
        //tableau[nombre]=0;//permet d'arrêter le timer
        return tableau;
    }
    else
    {
        return 0;
    }
}


/*
Uint32 generer_voitures(Uint32 intervalle, void *parametre)
{

    //int pos_x = parametre.pos_x;
    //int *pos_y = (int*) parametre.pos_y;
    //int sens_depart = parametre[2];
    struct donnees *tab=(donnees*) parametre;
    //int toto=tab.pos_x * 2;
    //tab.titine.push_back(new Voiture(tab.pos_x, tab.pos_y, tab.sens_depart));

    return intervalle;
}*/

void jouer(SDL_Surface* ecran)
{
    //génération des voitures
    //nécessite d'avoir enregistré toutes les positions de départ possibles
    int coords1[5][2]={{10,0},{24,0},{38,0},{52,0},{66,0}};//vertical descendant
    int coords2[5][2]={{69,10},{69,24},{69,38},{69,52},{69,66}};//horizontal droite->gauche
    int coords3[5][2]={{13,69},{27,69},{41,69},{55,69},{69,69}};//vertical ascendant
    int coords4[5][2]={{0,13},{0,27},{0,41},{0,55},{0,69}};//horizontal gauche->droite
    int coordonnees[4][5][2]={{{10,0},{24,0},{38,0},{52,0},{66,0}},{{69,10},{69,24},{69,38},{69,52},{69,66}},{{13,69},{27,69},{41,69},{55,69},{69,69}},{{0,13},{0,27},{0,41},{0,55},{0,69}}};

    //enregistrement des positions des feux
    int**** feux_haut=new int***[5];
    int**** feux_bas=new int***[5];
    int**** feux_droite=new int***[5];
    int**** feux_gauche=new int***[5];
    for(int i=0;i<5;i++)
    {
            feux_haut[i]=new int**[5];
            feux_bas[i]=new int**[5];
            feux_droite[i]=new int**[5];
            feux_gauche[i]=new int**[5];
            for(int j=0;j<5;j++)
            {
                    feux_haut[i][j]=new int*[3];
                    feux_bas[i][j]=new int*[3];
                    feux_droite[i][j]=new int*[3];
                    feux_gauche[i][j]=new int*[3];
                    for(int k=0;k<3;k++)
                    {
                            feux_haut[i][j][k]=new int[2];
                            feux_haut[i][j][k][0]=0;
                            feux_haut[i][j][k][1]=0;

                            feux_bas[i][j][k]=new int[2];
                            feux_bas[i][j][k][0]=0;
                            feux_bas[i][j][k][1]=0;

                            feux_droite[i][j][k]=new int[2];
                            feux_droite[i][j][k][0]=0;
                            feux_droite[i][j][k][1]=0;

                            feux_gauche[i][j][k]=new int[2];
                            feux_gauche[i][j][k][0]=0;
                            feux_gauche[i][j][k][1]=0;
                    }
            }
    }
    for(int j=0;j<=4;j++)
    {
        for(int i=0;i<=4;i++)
        {
            feux_haut[j][i][0][0]=10+i*14;
            feux_haut[j][i][0][1]=9+j*14;
            feux_haut[j][i][1][0]=11+i*14;
            feux_haut[j][i][1][1]=9+j*14;
            feux_haut[j][i][2][0]=3;
        }
    }
    for(int j=0;j<=3;j++)
    {
        for(int i=0;i<=4;i++)
        {
            feux_bas[j][i][0][0]=12+i*14;
            feux_bas[j][i][0][1]=14+j*14;
            feux_bas[j][i][1][0]=13+i*14;
            feux_bas[j][i][1][1]=14+j*14;
            feux_bas[j][i][2][0]=3;
        }
    }
    for(int j=0;j<=4;j++)
    {
        for(int i=0;i<=4;i++)
        {
            feux_gauche[j][i][0][0]=9+i*14;
            feux_gauche[j][i][0][1]=12+j*14;
            feux_gauche[j][i][1][0]=9+i*14;
            feux_gauche[j][i][1][1]=13+j*14;
            feux_gauche[j][i][2][0]=4;
        }
    }
    for(int j=0;j<=4;j++)
    {
        for(int i=0;i<=3;i++)
        {
            feux_droite[j][i][0][0]=14+i*14;
            feux_droite[j][i][0][1]=10+j*14;
            feux_droite[j][i][1][0]=14+i*14;
            feux_droite[j][i][1][1]=11+j*14;
            feux_droite[j][i][2][0]=4;
        }
    }

    double lambda=0.005;
    //int nombre=NB_TOTAL_VOITURES*20;

    //double* temps_generation=processus_poisson(lambda, nombre);
    //int * temps_generation = processus_poisson(lambda, nombre);srand(time(NULL));
        int * temps_generation= new int[NOMBRE];
        srand(time(NULL));
        for(int i=0;i<NOMBRE;i++)
        {
            temps_generation[i]=(-1/lambda)*log(1-(rand()/(double)RAND_MAX));
        }


/*

    for(int j=0;j<4;j++)
    {
        for(int i=0;i<5;i++)
        {
            //int *tab=new int[3];
            struct donnees tab;
            tab.pos_x=coordonnees_depart[j][i][0];
            tab.pos_y=coordonnees_depart[j][i][1];
            tab.sens_depart=j;
            timer[j][i] = SDL_AddTimer(temps_generation[p[j][i]], generer_voitures, &tab); //premier groupe de voitures
            //delete tab;
            (p[j][i]<nombre) ? p[j][i]++ : p[j][i]=nombre ;//arrête le timer

        }
    }*/


    Voiture *titine[NOMBRE];

    for(int i=0;i<NOMBRE;i++)
    {
        titine[i] = new Voiture();
    }

    //création globale
    SDL_Rect position;
    SDL_Surface *plein = NULL, *voiture = NULL, *feuvert = NULL, *feurouge = NULL, *objectif = NULL, *carrefour = NULL;
    SDL_Event event;

    //Initialisation
    int continuer = 1, objectifsRestants = 0, i = 0, j = 0, test=1;
    //int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {{0}};
    int**carte=new int*[NB_BLOCS_LARGEUR];
    int**carte2=new int*[NB_BLOCS_LARGEUR];
    for(int i=0;i<NB_BLOCS_LARGEUR;i++)
    {
        carte[i]=new int[NB_BLOCS_HAUTEUR];
        carte2[i]=new int[NB_BLOCS_HAUTEUR];
    }
    int tempsPrecedent = 0, tempsActuel = 0;

    //Chargement des sprites (décors, personnage...)
    //création globale
    plein = IMG_Load("mur.jpg");
    voiture = IMG_Load("mario_bas.gif");
    feuvert = IMG_Load("feu_vert.jpg");
    feurouge = IMG_Load("feu_rouge.jpg");
    objectif = IMG_Load("objectif.gif");
    carrefour = IMG_Load("carrefour.jpg");
    // Chargement du niveau
    if (!chargerNiveau(carte))
        exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau

    //Partie "continue" du jeu
    // Activation de la répétition des touches
    SDL_EnableKeyRepeat(100, 100);
    int debut=0;
    debut=SDL_GetTicks();
    int debut_generation=SDL_GetTicks();
    int initial=SDL_GetTicks();
    int indic=1;
    int nb_voitures=0;
    int nb_voitures2=0;
    int compteur=0;

    //for(int k=0;k<10;k++)
    while(continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        continuer = 0;
                        break;
                }
                break;
        }
        /*for(int j=0;j<4;j++)
        {
            for(int i=0;i<5;i++)
            {
                for(int k=0;k<NB_TOTAL_VOITURES;k++)
                {
                    if((actuel_generation-debut_generation)>=temps_generation[k])
                    {
                        titine[nb_voitures]=new Voiture(coordonnees_depart[j][i][0],coordonnees_depart[j][i][1],j);
                        nb_voitures++;
                        //(p[j][i]<NB_TOTAL_VOITURES) ? p[j][i]++ : p[j][i]=NB_TOTAL_VOITURES ;
                        debut_generation=actuel_generation;
                    }
                }
            }
        }*/

        int actuel_generation=0;
        actuel_generation=SDL_GetTicks();
        if(nb_voitures<NOMBRE)
        {
            if((actuel_generation-debut_generation)>=temps_generation[nb_voitures])
            {
                titine[nb_voitures]=new Voiture();
                nb_voitures++;
                nb_voitures2++;
                debut_generation=actuel_generation;
            }
        }
        /*
        for(int i=0;i<nombre;i++)
        {
            titine[i] = new Voiture();
        }*/



            int actuel=SDL_GetTicks();
            if (actuel-initial>DUREE_FEU )
            {
                switch(indic)
                {
                    case 1:
                    for (int j=0;j<=4;j++)
                    {
                        for (int i=0;i<=4;i++)
                        {
                            feux_haut[j][i][2][0]=4;
                            carte[feux_haut[j][i][0][0]][feux_haut[j][i][0][1]]=4;
                            carte[feux_haut[j][i][1][0]][feux_haut[j][i][1][1]]=4;
                            if(i<4)
                            {
                                feux_droite[j][i][2][0]=3;
                                carte[feux_droite[j][i][0][0]][feux_droite[j][i][0][1]]=3;
                                carte[feux_droite[j][i][1][0]][feux_droite[j][i][1][1]]=3;
                            }
                        }
                    }
                            indic++;
                initial=actuel;
                    break;

                    case 2:
                    for (int j=0;j<=4;j++)
                    {
                        for (int i=0;i<=4;i++)
                        {
                            if(i<4)
                            {
                            feux_droite[j][i][2][0]=4;
                            carte[feux_droite[j][i][0][0]][feux_droite[j][i][0][1]]=4;
                            carte[feux_droite[j][i][1][0]][feux_droite[j][i][1][1]]=4;
                            }
                            if(j<4)
                            {
                            feux_bas[j][i][2][0]=3;
                            carte[feux_bas[j][i][0][0]][feux_bas[j][i][0][1]]=3;
                            carte[feux_bas[j][i][1][0]][feux_bas[j][i][1][1]]=3;
                            }
                        }
                    }
                            indic++;
                initial=actuel;
                    break;

                    case 3:
                    for (int j=0;j<=4;j++)
                    {
                        for (int i=0;i<=4;i++)
                        {
                            if(j<4)
                            {
                            feux_bas[j][i][2][0]=4;
                            carte[feux_bas[j][i][0][0]][feux_bas[j][i][0][1]]=4;
                            carte[feux_bas[j][i][1][0]][feux_bas[j][i][1][1]]=4;
                            }
                            feux_gauche[j][i][2][0]=3;
                            carte[feux_gauche[j][i][0][0]][feux_gauche[j][i][0][1]]=3;
                            carte[feux_gauche[j][i][1][0]][feux_gauche[j][i][1][1]]=3;
                        }
                    }
                            indic++;
                initial=actuel;
                    break;

                    case 4:
                    for (int j=0;j<=4;j++)
                    {
                        for (int i=0;i<=4;i++)
                        {
                            feux_gauche[j][i][2][0]=4;
                            carte[feux_gauche[j][i][0][0]][feux_gauche[j][i][0][1]]=4;
                            carte[feux_gauche[j][i][1][0]][feux_gauche[j][i][1][1]]=4;
                            feux_haut[j][i][2][0]=3;
                            carte[feux_haut[j][i][0][0]][feux_haut[j][i][0][1]]=3;
                            carte[feux_haut[j][i][1][0]][feux_haut[j][i][1][1]]=3;
                        }
                    }
                            indic=1;
                initial=actuel;
                    break;

                }
            }/*
            else
            {
                SDL_Delay(DUREE_FEU -(actuel-initial));
            }*/


            tempsActuel = SDL_GetTicks();
            /* Si LATENCE ms se sont écoulées depuis le dernier tour de boucle */
            if (tempsActuel>(LATENCE+tempsPrecedent))
            {
                for(int i=0;i<nb_voitures;i++)
                {
                    titine[i]->test_trajectoire(carte, carte2, ecran);
                    if(titine[i]->test_objectif(carte2, ecran))
                    {
                        delete titine[i];
                        //nb_voitures2--;
                    }
                }
                tempsPrecedent = tempsActuel;
            }/*
            else // Si ça fait moins de LATENCE ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut
            {
                SDL_Delay(LATENCE - (tempsActuel - tempsPrecedent));
            }*/

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));


        // Placement des objets à l'écran
        objectifsRestants = 0;

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
                    case FEUVERT:
                        SDL_BlitSurface(feuvert, NULL, ecran, &position);
                        break;
                    case FEUROUGE:
                        SDL_BlitSurface(feurouge, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        objectifsRestants++;
                        break;
                    case CARREFOUR:
                        SDL_BlitSurface(carrefour, NULL, ecran, &position);
                        break;
                }
            }
        }

        for(int i=0;i<nb_voitures;i++)
        {
            titine[i]->blitage(ecran);
        }


        SDL_Flip(ecran);

        }
//fclose(file);

    // Désactivation de la répétition des touches (remise à 0)
    SDL_EnableKeyRepeat(0, 0);

    // Libération des surfaces chargées
    SDL_FreeSurface(plein);
    SDL_FreeSurface(feuvert);
    SDL_FreeSurface(feurouge);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(carrefour);

    for (int i = 0 ; i < nb_voitures ; i++)
    {
        titine[i]->liberation();
    }
}

void Voiture::deplacer(int** carte, int** carte2, int direction, SDL_Surface* ecran)
{
FILE* fichier = NULL;
fichier = fopen("deplacer.txt", "a");

                    fprintf(fichier, "Voiture coords x %d ", m_positionVoiture.x);
                    fprintf(fichier, "Voiture coords y %d ", m_positionVoiture.y);
                    fprintf(fichier, "Objectif coords x %d ", m_positionObjectif.x);
                    fprintf(fichier, "Objectif coords y %d\n", m_positionObjectif.y);
    switch(direction)
    {
        case HAUT:
            if (m_positionVoiture.y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
            {
                m_position_memoire--;
                break;
                //fprintf(fichier, "negatif %d", 1);
            }
            else if (carte[m_positionVoiture.x][m_positionVoiture.y - 1] == PLEIN || carte2[m_positionVoiture.x][m_positionVoiture.y - 1] == VOITURE) // S'il y a un mur OU une voiture, on arrête
            {
                m_position_memoire--;
                break;
                //fprintf(fichier, "voiture %d", 1);
            }
            else
            {
            carte2[m_positionVoiture.x][m_positionVoiture.y] = VIDE;
            m_positionVoiture.y--; // On peut enfin faire monter le joueur
            carte2[m_positionVoiture.x][m_positionVoiture.y] = VOITURE;//on indique qu'il y a une voiture
            //test_objectif(carte2, ecran);
            //blitage(ecran);
            //fprintf(fichier, "%d ", m_positionVoiture.y);
            }
            break;


        case BAS:
            if (m_positionVoiture.y + 1 >= NB_BLOCS_HAUTEUR)
                {
                    m_position_memoire--;
                    break;
                }
            if (carte[m_positionVoiture.x][m_positionVoiture.y + 1] == PLEIN || carte2[m_positionVoiture.x][m_positionVoiture.y + 1] == VOITURE)
                {
                    m_position_memoire--;
                    break;
                }

            carte2[m_positionVoiture.x][m_positionVoiture.y] = VIDE;
            m_positionVoiture.y++;
            carte2[m_positionVoiture.x][m_positionVoiture.y] = VOITURE;
            //test_objectif(carte2, ecran);
            //blitage(ecran);
            break;


        case GAUCHE:
            if (m_positionVoiture.x - 1 < 0)
            {
                m_position_memoire--;
                break;
            }
            if (carte[m_positionVoiture.x - 1][m_positionVoiture.y] == PLEIN || carte2[m_positionVoiture.x - 1][m_positionVoiture.y] == VOITURE)
            {
                m_position_memoire--;
                break;
            }

            carte2[m_positionVoiture.x][m_positionVoiture.y] = VIDE;
            m_positionVoiture.x--;
            carte2[m_positionVoiture.x][m_positionVoiture.y] = VOITURE;
            //test_objectif(carte2, ecran);
            //blitage(ecran);
            break;


        case DROITE:
            if (m_positionVoiture.x + 1 >= NB_BLOCS_LARGEUR)
            {
                m_position_memoire--;
                break;
            }

            if (carte[m_positionVoiture.x + 1][m_positionVoiture.y] == PLEIN || carte2[m_positionVoiture.x + 1][m_positionVoiture.y] == VOITURE)
            {
                m_position_memoire--;
                break;
            }

            carte2[m_positionVoiture.x][m_positionVoiture.y] = VIDE;
            m_positionVoiture.x++;
            carte2[m_positionVoiture.x][m_positionVoiture.y] = VOITURE;
            //test_objectif(carte2, ecran);
            //blitage(ecran);
            break;
    }
fclose(fichier);
}
