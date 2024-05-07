#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HAUTEUR 100
#define LARGEUR 100


void afficheCam(char tab[LARGEUR][HAUTEUR], int x, int y, int l, int h){
    for (int i = x-h; i < x+h; i++){
        for (int j = y-l; j < y+l; j++){
            if (i < 0 || j < 0 || j > LARGEUR || i > HAUTEUR){
                exit(1);
            }
            printf("%c", tab[i][j]);
        }
        printf("\n");
        printf("sucemaqueueantonin\n");
    }
}    