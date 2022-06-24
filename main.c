/* Librairies */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constantes */
#define COTE 10

/* Coordonnees dans la matrice */
struct coordonnees {
    int i;
    int j;
};
typedef struct coordonnees coordonnees;


/* Initialise à t=0 */
void init0(char** matrice) {
    for (int i=0; i<COTE; i++) {
        for (int j=0; j<COTE; j++) {
            matrice[i][j] = '~';
        }
    }

    matrice[0][0] = 'T';

    matrice[7][3] = 'R';
}

/* Affiche une matrice de taille N */
void displayMatrice(char** matrice) {
    for (int i=0; i<COTE; i++) {
        for (int j=0; j<COTE; j++) {
            printf("%c", matrice[i][j]);
        }
        printf("\n");
    }
}

/* Recherche où se trouve la tondeuse T dans une matrice de taille N */
coordonnees searchMowerT(char** matrice) {
    coordonnees c;
    for (int i=0; i<COTE; i++) {
        for (int j=0; j<COTE; j++) {
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

/* Recherche où se trouve la tondeuse R dans une matrice de taille N */
coordonnees searchMowerR(char** matrice) {
    coordonnees c;
    for (int i=0; i<COTE; i++) {
        for (int j=0; j<COTE; j++) {
            if (matrice[i][j] == 'R') {
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
    for (int i=0; i<COTE; i++) {
        for (int j=0; j<COTE; j++) {
            if (matrice[i][j] == '~') {
                return 1;
            }
        }
    }
    printf("\nTout le gazon a ete tondu :D\n");
    return 0;
}

/* t --> t+1 */
void next1(char** matrice, coordonnees* lastPos) {
    coordonnees t = searchMowerT(matrice);
    coordonnees aux = {lastPos->i, lastPos->j};
    if (t.i == -1 && t.j == -1) {
        printf("Plus rien a tondre :(\n");
    }
    else {
        if ((lastPos->i==t.i && lastPos->j+1==t.j) || (lastPos->j==0 && lastPos->i+1==t.i)) {
            if (t.j!=COTE-1) {
                matrice[t.i][t.j] = '_';
                matrice[t.i][t.j+1] = 'T';
            }
            else {
                matrice[t.i][t.j] = '_';
                matrice[t.i+1][t.j] = 'T';
            }
        }
        else {
            if (t.j!=0) {
                matrice[t.i][t.j] = '_';
                matrice[t.i][t.j-1] = 'T';
            }
            else {
                matrice[t.i][t.j] = '_';
                matrice[t.i+1][t.j] = 'T';
            }
        }
    }
    lastPos->i = t.i;
    lastPos->j = t.j;
}

/* t --> t+1 */
void next2(char** matrice) {
    coordonnees t = searchMowerR(matrice);
    int i, j;
    if (t.i == -1 && t.j == -1) {
        printf("Plus rien a tondre :(\n");
    }
    else {
        // Genere un nombre aleatoire entre 0 et COTE
        i = rand() % COTE;
        j = rand() % COTE;
        matrice[t.i][t.j] = '_';
        matrice[i][j] = 'R';
    }
}

int main() {
    char** mat = malloc(COTE*sizeof(char*));

    for (int i=0; i<COTE; i++) {
        mat[i] = malloc(COTE*sizeof(char));
    }

    init0(mat);
    displayMatrice(mat);

    int i = 1;
    int l = 1;
    coordonnees lastPos = {0,-1};

    while (presenceOfGrass(mat) && l<=10) {
        printf("\n-------------------------------------\n");
        printf("t = %d\n", i);
        next1(mat, &lastPos);
        next2(mat);
        displayMatrice(mat);
        i++;
        l++;
    }

    free(mat);
    return EXIT_SUCCESS;
}
