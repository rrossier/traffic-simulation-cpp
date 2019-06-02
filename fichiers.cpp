/*
fichiers.cpp
----------

fonctions de lecture / écriture de fichiers de niveau.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <time.h>

#include "constantes.h"
#include "fichiers.h"

int chargerNiveau(int** niveau)
{
    FILE* fichier = NULL;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
    long int i = 0, j = 0;

    fichier = fopen("niveaux.lvl", "r");
    if (fichier == NULL)
        return 0;

    fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
            {
                case '0':
                    niveau[j][i] = 0;
                    break;
                case '1':
                    niveau[j][i] = 1;
                    break;
                case '2':
                    niveau[j][i] = 2;
                    break;
                case '3':
                    niveau[j][i] = 3;
                    break;
                case '4':
                    niveau[j][i] = 4;
                    break;
                case '5':
                    niveau[j][i] = 5;
                    break;
                case '6':
                    niveau[j][i] = 6;
                    break;
            }
        }
    }

    fclose(fichier);
    return 1;
}


int sauvegarderNiveau(int** niveau)
{
    FILE* fichier = NULL;
    int i = 0, j = 0;

    fichier = fopen("niveaux.lvl", "w");
    if (fichier == NULL)
        return 0;

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            fprintf(fichier, "%d", niveau[j][i]);
        }
    }

    fclose(fichier);
    return 1;
}

long fact(int i)
{
       long f;

       if (i==0 || i<0)
       {
          return 1;
       }
       else
       {
           f = fact(i - 1);
           return i*f;
       }

}


double generateur_poisson(int k, int n)
{
    double e, p, q, r, t, x, y, z;

     //printf("entrez la valeur de k entier non nul positif\n");
     //scanf("%d", &k);
     //printf("entrez le nombre d'essais n entier non nul positif\n");
     //scanf("%d", &n);

     x = fact(n);
     y = fact(k);
     z = fact(n-k);
     r = x/(y*z);

     //printf("la combinaison n de k est : %lf\n", r);

     x = n-1;
     y = k-1;
     z = x-y;
     x = fact(x);
     y = fact(y);
     z = fact(z);
     e = x/(y*z);
     e = e/x;
     p = pow(e, k);

     //printf("la probabilite de succes k de n est : %lf\n", p);

     x = n-k;
     y = 1-p;
     q = pow(y, x);
     r = r*p*q;
     //printf("le resultat de la loi binomiale est : %lf\n", r);
     e = n*p;
     //printf("l'esperance est de : %lf\n", e);
     t = sqrt(e*q);
     //printf("l'ecart type est de : %lf\n", t);

     x = exp(-e);
     y = pow (e,k);
     z = x*y;
     k = fact(k);
     x = z/k;
     //printf("la loi de poisson est : %g\n", x);

     return x;
}

