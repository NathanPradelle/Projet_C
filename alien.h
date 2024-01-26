#ifndef ALIEN_H
#define ALIEN_H

typedef struct Alien {
    long id;
    int alive;
    int health;
    int x;
    int y;
    int width;
    int height;
    float speed;
    int travelDistance;
    int age;
    float lifespan;
    short satiety;
    short eatDamage;
    int time;
    short type;
    int deplacment;
    int *race;
    struct Alien *next;
} Alien;

Alien *creerAlien(int *numberOfAliens);
void detruireAlien(Alien *alien);
void deplacerAlien(Alien *alien);
void ajouterAlien(Alien **liste, int *numberOfAliens);
void ajouterAlienDepuisFichier(Alien **liste, int *numberOfAliens, long id, int x, int y);
void viderListeAliens(Alien **listeAliens);
void supprimerAlien(Alien **listeAliens, Alien *alien);

#endif