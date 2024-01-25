#include "alien.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

int alienConfig(int * defaultSpeed) {
    FILE *configFile = fopen("config.txt", "r");
    if (configFile == NULL) {
        perror("Impossible d'ouvrir le fichier de configuration");
        return 1;
    }

    char line[150];
    while (fgets(line, sizeof(line), configFile) != NULL) {
        sscanf(line, "DEFAULT_SPEED=%d", defaultSpeed);
    }

    fclose(configFile);
    return 0;
}

Alien *creerAlien(int *numberOfAliens) {
    int defaultSpeed = 0;
    alienConfig(&defaultSpeed);

    ++*numberOfAliens;
    Alien *nouvelAlien = (Alien *)malloc(sizeof(Alien));
    if (nouvelAlien != NULL) {
        nouvelAlien->id = *numberOfAliens;
        nouvelAlien->x = rand() % screenWidth;
        nouvelAlien->y = rand() % screenHeight;
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
                alien->y -= alien->speed;
            }
            break;
        case 1:
            if (alien->y < 885) {  
                alien->y += alien->speed;
            }
            break;
        case 2:
            if (alien->x > 15) {
                alien->x -= alien->speed;
            }
            break;
        case 3:
            if (alien->x < 1585) {  
                alien->x += alien->speed;
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