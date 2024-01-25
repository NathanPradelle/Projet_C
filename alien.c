#include "alien.h"
#include <stdio.h>
#include <stdlib.h>

Alien *creerAlien(int *numberOfAliens) {
    ++*numberOfAliens;
    Alien *nouvelAlien = (Alien *)malloc(sizeof(Alien));
    if (nouvelAlien != NULL) {
        nouvelAlien->alive=1;
        nouvelAlien->id = *numberOfAliens;
        nouvelAlien->x = rand() % 400;
        nouvelAlien->y = rand() % 400;
        nouvelAlien->day = 0;
        nouvelAlien->type = rand() % 3;
        nouvelAlien->next = NULL;
    }
    return nouvelAlien;
}

void detruireAlien(Alien *alien) {
    free(alien);
}



void deplacerAlien(Alien *alien) {

    alien->day++;

    int direction = rand() % 5;
    switch (direction) {
        case 0:
            if (alien->y > 15) {
                alien->y -= 15;
            }
            break;
        case 1:
            if (alien->y < 400-15) {  
                alien->y += 15;
            }
            break;
        case 2:
            if (alien->x > 15) {
                alien->x -= 15;
            }
            break;
        case 3:
            if (alien->x < 400-15) {  
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