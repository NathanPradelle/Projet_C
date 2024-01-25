#ifndef ALIEN_H
#define ALIEN_H

typedef struct Alien {
    int alive;
    int id;
    int x;
    int y;
    int day;
    int type;
    struct Alien *next;
} Alien;

Alien *creerAlien(int *numberOfAliens);
void detruireAlien(Alien *alien);
void deplacerAlien(Alien *alien);
void ajouterAlien(Alien **liste, int *numberOfAliens);


#endif