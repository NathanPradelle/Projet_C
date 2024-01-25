#include "alien.h"
#include <stdio.h>
#include <stdlib.h>

Alien *creerAlien(int *numberOfAliens) {
    ++*numberOfAliens;
    Alien *nouvelAlien = (Alien *)malloc(sizeof(Alien));
    if (nouvelAlien != NULL) {
        nouvelAlien->id = *numberOfAliens;
        nouvelAlien->x = rand() % 1600;
        nouvelAlien->y = rand() % 900;
        nouvelAlien->next = NULL;
    }
    return nouvelAlien;
}

void detruireAlien(Alien *alien) {
    free(alien);
}

void deplacerAlien(Alien *alien) {
    int direction = rand() % 4;

    switch (direction) {
        case 0:
            if (alien->y > 15) {
                alien->y -= 15;
            }
            break;
        case 1:
            if (alien->y < 885) {  
                alien->y += 15;
            }
            break;
        case 2:
            if (alien->x > 15) {
                alien->x -= 15;
            }
            break;
        case 3:
            if (alien->x < 1585) {  
                alien->x += 15;
            }
            break;
    }
}


void ajouterAlien(Alien **liste, int *numberOfAliens) {
    Alien *nouvelAlien = creerAlien(numberOfAliens);
    if (nouvelAlien != NULL) {
        if (*liste == NULL) {
            *liste = nouvelAlien;
        } else {
            Alien *courant = *liste;
            while (courant->next != NULL) {
                courant = courant->next;
            }
            courant->next = nouvelAlien;
        }
    }
}