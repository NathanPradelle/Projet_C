#titre Commande avec les bonnes options pour pouvoir compiler le projet :  
gcc -o mon_programme main.c -std=c11 -Wall -Wextra -I./vendor/include -L./vendor/lib -lSDL2 -Wl,-subsystem,windows -DSDL_MAIN_HANDLED
