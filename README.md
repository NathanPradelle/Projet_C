## Commande avec les bonnes options pour pouvoir compiler le projet :  
gcc -o alien_simulation main.c graphics.c alien.c -std=c11 -Wall -Wextra -I./vendor/include -L./vendor/lib -lSDL2_ttf -lSDL2 -Wl,-subsystem,windows -DSDL_MAIN_HANDLED

## Commande pour compiler le menu :  
gcc -o menu menu.c -std=c11 -Wall -Wextra -I./vendor/include -L./vendor/lib -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2 -Wl,-subsystem,windows -DSDL_MAIN_HANDLED


## Commande simplifier pour compiler la simulation
make (oui, t'écris juste ça dans MSYS2 est ça va tout compiler)

## Commande pour lancer le programme
./alien_simulation.exe

## Ajouter un fichier à la compilation
Dans le fichier Makefile, rajoute le nom du fichier dans la ligne avec SRCS
Attention, ne pas modifier la tabulation du fichier
