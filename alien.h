#ifndef ALIEN_H
#define ALIEN_H

typedef struct Alien {
    long id;
    int alive;
    int health;
    int x;
    int y;
    float speed;
    int travelDistance;
    int width;
    int height;
    int age;
    float lifespan;
    int satiety;
    int eatDamage;
    int time;
    int type;
    struct Race *race;
    struct Alien *next;
} Alien;

typedef struct Race {
    long id;
    char *name;
    short *color;
    char *like;
    char *dislike;
} Race;

// Une mutation est juste une modification de ces valeurs


Alien *creerAlien(int *numberOfAliens);
void detruireAlien(Alien *alien);
void deplacerAlien(Alien *alien);
void ajouterAlien(Alien **liste, int *numberOfAliens);
void ajouterAlienDepuisFichier(Alien **liste, int *numberOfAliens, long id, int x, int y);
void viderListeAliens(Alien **listeAliens);
void supprimerAlien(Alien **listeAliens, Alien *alien);

#endif