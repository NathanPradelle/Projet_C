#include "alien.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

int alienConfig(int *defaultSpeed, int *alienTravelDistance, int *alienWidth, int *alienHeight) {
    FILE *configFile = fopen("config.txt", "r");
    if (configFile == NULL) {
        perror("Impossible d'ouvrir le fichier de configuration");
        return 1;
    }

    char line[150];
    while (fgets(line, sizeof(line), configFile) != NULL) {
        sscanf(line, "DEFAULT_SPEED=%d", defaultSpeed);
        sscanf(line, "DEFAULT_TRAVEL_DISTANCE=%d", alienTravelDistance);
        sscanf(line, "ALIEN_WIDTH=%d", alienWidth);
        sscanf(line, "ALIEN_HEIGHT=%d", alienHeight);
    }

    fclose(configFile);
    return 0;
}

Alien *creerAlien(int *numberOfAliens) {
    int defaultSpeed, alienTravelDistance, alienWidth, alienHeight = 5;
    
    alienConfig(&defaultSpeed, &alienTravelDistance, &alienWidth, &alienHeight);

    ++*numberOfAliens;
    Alien *nouvelAlien = (Alien *)malloc(sizeof(Alien));
    if (nouvelAlien != NULL) {
        nouvelAlien->id = *numberOfAliens;
        nouvelAlien->x = rand() % screenWidth;
        nouvelAlien->y = rand() % screenHeight;
        nouvelAlien->speed = defaultSpeed;
        nouvelAlien->travelDistance = alienTravelDistance;
        nouvelAlien->width = alienWidth;
        nouvelAlien->height = alienHeight;
        nouvelAlien->next = NULL;
    }
    return nouvelAlien;
}

void detruireAlien(Alien *alien) {
    free(alien);
}

void deplacerAlien(Alien *alien, int tempsint) {
    int direction = rand() % 4;

    if (tempsint % alien->speed == 0) {
        switch (direction) {
            case 0:
                if (alien->y > 15) {
                    alien->y -= alien->travelDistance;
                }
                break;
            case 1:
                if (alien->y < 885) {  
                    alien->y += alien->travelDistance;
                }
                break;
            case 2:
                if (alien->x > 15) {
                    alien->x -= alien->travelDistance;
                }
                break;
            case 3:
                if (alien->x < 1585) {  
                    alien->x += alien->travelDistance;
                }
                break;
        }
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