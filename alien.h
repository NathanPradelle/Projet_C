#ifndef ALIEN_H
#define ALIEN_H

typedef struct Alien {
    long id;
    int health;
    int x;
    int y;
    int speed;
    int size;
    int age;
    int satiety;
    int eatDamage;
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

#endif