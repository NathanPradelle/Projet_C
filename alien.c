#include "alien.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

int alienConfig(float *defaultSpeed, int *alienTravelDistance, int *alienWidth, int *alienHeight) {
    FILE *configFile = fopen("config.txt", "r");
    if (configFile == NULL) {
        perror("Impossible d'ouvrir le fichier de configuration");
        return 1;
    }

    char line[150];
    while (fgets(line, sizeof(line), configFile) != NULL) {
        sscanf(line, "DEFAULT_SPEED=%f", defaultSpeed);
        sscanf(line, "DEFAULT_TRAVEL_DISTANCE=%d", alienTravelDistance);
        sscanf(line, "ALIEN_WIDTH=%d", alienWidth);
        sscanf(line, "ALIEN_HEIGHT=%d", alienHeight);
    }

    fclose(configFile);
    return 0;
}

Alien *creerAlien(int *numberOfAliens) {
    float defaultSpeed = 0;
    int alienTravelDistance, alienWidth, alienHeight = 5;
    
    alienConfig(&defaultSpeed, &alienTravelDistance, &alienWidth, &alienHeight);

    ++*numberOfAliens;
    Alien *nouvelAlien = (Alien *)malloc(sizeof(Alien));
    if (nouvelAlien != NULL) {
        nouvelAlien->alive=1;
        nouvelAlien->id = *numberOfAliens;
        nouvelAlien->x = rand() % (screenWidth - alienWidth);
        nouvelAlien->y = rand() % (screenHeight - alienHeight);
        nouvelAlien->speed = defaultSpeed;
        nouvelAlien->travelDistance = alienTravelDistance;
        nouvelAlien->width = alienWidth;
        nouvelAlien->height = alienHeight;
        nouvelAlien->time = 0;
        nouvelAlien->age = 0;
        nouvelAlien->type = rand() % 3;
        nouvelAlien->next = NULL;
    }
    return nouvelAlien;
}

void detruireAlien(Alien *alien) {
    free(alien);
}

void deplacerAlien(Alien *alien) {
    int direction = rand() % 4;

    alien->age++;
    alien->time++;

    if (alien->time * alien->speed > 100) {
        switch (direction) {
            case 0:
                if (alien->y > alien->height) {
                    alien->y -= alien->travelDistance;
                }
                break;
            case 1:
                if (alien->y < screenHeight - alien->height) {  
                    alien->y += alien->travelDistance;
                }
                break;
            case 2:
                if (alien->x > alien->width) {
                    alien->x -= alien->travelDistance;
                }
                break;
            case 3:
                if (alien->x < screenWidth - alien->width) {  
                    alien->x += alien->travelDistance;
                }
                break;
        }
        alien->time = 0;
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
