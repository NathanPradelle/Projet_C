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

#endif