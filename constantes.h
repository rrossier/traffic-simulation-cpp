/*
constantes.h
*/

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

    #define TAILLE_BLOC         10 // Taille d'un bloc (carré) en pixels
    #define NB_BLOCS_LARGEUR    70
    #define NB_BLOCS_HAUTEUR    70
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
    #define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR
    #define LATENCE             200
    #define DUREE_FEU           2600
    #define NB_TOTAL_VOITURES   20
    #define NOMBRE              NB_TOTAL_VOITURES*20


    enum {HAUT, BAS, GAUCHE, DROITE};
    enum {VIDE, PLEIN, VOITURE, FEUVERT, FEUROUGE, OBJECTIF, CARREFOUR};

#endif

