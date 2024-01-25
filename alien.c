#include "alien.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

Alien *creerAlien(int *numberOfAliens) {
    ++*numberOfAliens;
    Alien *nouvelAlien = (Alien *)malloc(sizeof(Alien));
    if (nouvelAlien != NULL) {
        nouvelAlien->id = *numberOfAliens;
        nouvelAlien->x = rand() % (screenWidth - alienWidth);
        nouvelAlien->y = rand() % (screenHeight - alienHeight);
        nouvelAlien->next = NULL;
    }
    return nouvelAlien;
}

void detruireAlien(Alien *alien) {
    free(alien);
}

void deplacerAlien(Alien *alien) {
    int direction = rand() % 5;

    switch (direction) {
        case 0:
            if (alien->y > alienHeight) {
                alien->y -= 1;
            }
            break;
        case 1:
            if (alien->y < screenHeight - alienHeight) {  
                alien->y += 1;
            }
            break;
        case 2:
            if (alien->x > alienWidth) {
                alien->x -= 1;
            }
            break;
        case 3:
            if (alien->x < screenWidth - alienWidth) {  
                alien->x += 1;
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