#ifndef ALIEN_H
#define ALIEN_H

typedef struct Alien {
    int id;
    int x;
    int y;
    struct Alien *next;
} Alien;

Alien *creerAlien(Alien **liste);
void detruireAlien(Alien *alien);
void deplacerAlien(Alien *alien);
void ajouterAlien(Alien **liste);

#endif