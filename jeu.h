/*
jeu.h
prototypes
*/

#ifndef DEF_JEU
#define DEF_JEU

    void jouer(SDL_Surface* ecran);
    //int***** enregistrements_feux();
    //Uint32 generer_voitures(Uint32 intervalle, void *parametre);
    int *processus_poisson(double lambda, int nombre);

class Voiture
{
    public:
    Voiture();
    //~Voiture();
    //Voiture(int pos_x, int pos_y, int direction);
    //Voiture(int numero, int pos_x, int pos_y, float vitesse, int sens_depart);
    void test_feu();
    void test_trajectoire(int** carte, int** carte2, SDL_Surface *ecran);
    void deplacer(int** carte, int** carte2, int direction, SDL_Surface *ecran);
    //void test_feu(int** carte);
    void blitage(SDL_Surface *ecran);
    void liberation();
    //void test_collision();
    int test_objectif(int** carte2, SDL_Surface *ecran);
    void retrouver_positions();
    int getNumber() const;
    int getpos_x() const;
    int getpos_y() const;

    private:
    int m_numero;//numero de la voiture
    int m_pos_x;//position x
    int m_pos_y;//position y
    float m_vitesse;//vitesse de la voiture
    int m_sens_deplacement;
    int m_voie_deplacement;
    int m_temps_depart;
    int m_temps_attente;
    int m_temps_buffer;
    bool m_objectif_atteint;
    int m_memoire[10];//mémoire après une décision de direction prise
    int m_position_memoire;//position dans le tableau m_memoire, sera pê inutile avec la nouvelle version
    SDL_Surface *m_vue[4], *m_vue_actuelle;
    SDL_Rect m_position, m_positionVoiture, m_positionObjectif;
};

/*
struct donnees
    {
        int pos_x;
        int pos_y;
        int sens_depart;
        Voiture titine;
    };
    */

#endif

