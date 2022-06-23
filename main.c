/* Librairies */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Programmes */
#include "merseneTwister.c"

/* Constantes */
#define N 10

/* Coordonnees dans la matrice */
struct coordonnees {
    int i;
    int j;
};
typedef struct coordonnees coordonnees;


/* Initialise à t=0 */
void init0(char** matrice) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            matrice[i][j] = '~';
        }
    }

    matrice[0][0] = 'T';
}

/* Affiche une matrice de taille N */
void displayMatrice(char** matrice) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            printf("%c", matrice[i][j]);
        }
        printf("\n");
    }
}

/* Recherche où se trouve la tondeuse T dans une matrice de taille N */
coordonnees searchMowerT(char** matrice) {
    coordonnees c;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (matrice[i][j] == 'T') {
                c.i = i;
                c.j = j;
                return c;
            }
        }
    }
    /* On ne trouve pas T */
    c.i = -1;
    c.j = -1;
    return c;
}

/* Verifie s'il reste du gazon a tendre */
int presenceOfGrass(char** matrice) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (matrice[i][j] == '~') {
                return 1;
            }
        }
    }
    printf("\nTout le gazon a ete tondu :D\n");
    return 0;
}

/* t --> t+1 */
void next(char** matrice) {
    coordonnees t = searchMowerT(matrice);
    if (t.i == -1 && t.j == -1) {
        printf("Plus rien a tondre :(\n");
    }
    else {
        if (t.j == 0) { 
            /* Si on est sur la première colonne */
            if (matrice[t.i][t.j+1] == '~') {
                matrice[t.i][t.j] = '_';
                matrice[t.i][t.j+1] = 'T';
            }
            else {
                if (t.i < N-1) {
                    matrice[t.i][t.j] = '_';
                    matrice[t.i+1][t.j] = 'T';
                }
                else {
                    matrice[t.i][t.j] = '_';
                    printf("La tonte est finie :)\n");
                }
            }
        }
        else {
            if (t.j == N-1) {
                /* Si on est sur la dernière colonne */
                if (matrice[t.i][t.j-1] == '~') {
                    matrice[t.i][t.j] = '_';
                    matrice[t.i][t.j-1] = 'T';
                }
                else {
                    if (t.i < N-1) {
                        matrice[t.i][t.j] = '_';
                        matrice[t.i+1][t.j] = 'T';
                    }
                    else {
                        matrice[t.i][t.j] = '_';
                        printf("La tonte est finie :)\n");
                    }
                }
            }
            else {
                /* Si on est vers le milieu des colonnes */
                if (matrice[t.i][t.j+1] == '~') {
                    matrice[t.i][t.j] = '_';
                    matrice[t.i][t.j+1] = 'T';
                }
                else {
                    matrice[t.i][t.j] = '_';
                    matrice[t.i][t.j-1] = 'T';
                }
            }
        }
    }
}

int main() {
    char** mat = malloc(N*sizeof(char*));

    for (int i=0; i<N; i++) {
        mat[i] = malloc(N*sizeof(char));
    }

    init0(mat);
    displayMatrice(mat);

    int i = 1;

    while (presenceOfGrass(mat)) {
        printf("\n-------------------------------------\n");
        printf("t = %d\n", i);
        next(mat);
        displayMatrice(mat);
        i++;
    }

    free(mat);
    return EXIT_SUCCESS;
}