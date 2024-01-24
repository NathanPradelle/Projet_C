#include "alien.h"
#include <stdlib.h>

Alien *creerAlien(Alien **liste) {
    Alien *nouvelAlien = (Alien *)malloc(sizeof(Alien));
    if (nouvelAlien != NULL) {
        nouvelAlien->id = rand();
        nouvelAlien->x = rand() % 1600;
        nouvelAlien->y = rand() % 900;
        nouvelAlien->next = *liste;
    }
    return nouvelAlien;
}

void detruireAlien(Alien *alien) {
    free(alien);
}

void deplacerAlien(Alien *alien) {
    int direction = rand() % 4; /

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

void ajouterAlien(Alien **liste) {
    Alien *nouvelAlien = creerAlien(liste);
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