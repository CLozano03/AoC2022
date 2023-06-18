/**
 *  Compilar: gcc Dia08_2.c -o Dia08_2
 *  Ejecutar: Dia08_2.exe input.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tamaño de la matriz */
#define FOREST_SIZE 99
#define true 1
#define false 0

/* Cabeceras */
int calculate_scenic_score(int** forest, int x, int y);

int max_scenic_score(int** forest) {
    int result = -1, actual, i, j;

    for(i = 0; i < FOREST_SIZE; i++){
        for(j = 0; j < FOREST_SIZE; j++){
            actual = calculate_scenic_score(forest, i, j);
            if(actual > result){
                result = actual;
            }
        }
    }
    return result;
}       

int calculate_scenic_score(int** forest, int x, int y){
    /* Defino resultado para cualquier posible punto cardinal */
    int result_h_1 = 0, result_h_2 = 0;
    int result_v_1 = 0, result_v_2 = 0;
    int stop = false;

    int i, j;
    int tree_size = forest[x][y]; /* Arbol que queremos comparar */ 

    /* ----Comprobacion horizontal---- */
    /* IZQUIERDA del arbol */
    for(j = y - 1; j > -1 && !stop; j--){
        result_h_1++;
        if(forest[x][j] >= tree_size)
            stop = true;
    }
    /* DERECHA del arbol */
    stop = false;
    for(j = y + 1; j < FOREST_SIZE && !stop; j++){
        result_h_2++;
        if(forest[x][j] >= tree_size)
            stop = true;
    }

    /* ----Comprobacion vertical---- */
    /* ARRIBA del arbol */
    stop = false;
    for(i = x - 1; i > -1 && !stop; i--){
        result_v_1++;
        if(forest[i][y] >= tree_size)
            stop = true;
    }
    /* DEBAJO del arbol */
    stop = false;
    for(i = x + 1; i < FOREST_SIZE && !stop; i++){
        result_v_2++;
        if(forest[i][y] >= tree_size)
            stop = true;
    }

    return result_h_1 * result_v_1 * result_h_2 * result_v_2;
}

void parse_file(FILE* f, int** forest){
    int i, j;
    char linea[FOREST_SIZE + 1];
    char read;
    for(i = 0; i < FOREST_SIZE; i++){
        fgets(linea, FOREST_SIZE + 2, f);
        /* Quinamos los \n. En la ultima linea hay EOF*/
        if(i != 98)
            linea[strlen(linea)-1] = '\0';
        /* Metemos el digito en la matriz */
        for(j = 0; j < FOREST_SIZE; j++){
            forest[i][j] = linea[j] - '0';
        }
    }
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char* argv[]){
    FILE* f; 
    f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    /* Crear la matriz bosque, asignando memoria dinamica */
    int i;
    int** forest = (int**)malloc(FOREST_SIZE * sizeof(int*));
    for (i = 0; i < FOREST_SIZE; i++) {
        forest[i] = (int*)malloc(FOREST_SIZE * sizeof(int));
    }

    /* Parseo de archivo */
    parse_file(f, forest);
    fclose(f); 

    /* Operacion de cuenta */
    int max_score = max_scenic_score(forest);

    /* Imprimir resultado */
    printf("\nArboles visibles: %d\n", max_score);

    /* Liberar memoria asignada al bosque */
    for (i = 0; i < FOREST_SIZE; i++) {
        free(forest[i]);
    }
    free(forest);

    return 0;
}