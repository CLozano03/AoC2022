/**
 *  Compilar: gcc Dia08_1.c -o Dia08_1
 *  Ejecutar: Dia08_1.exe input.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A simple vista, vemos que en el input nos ponen un bosque
cuadrado de 99x99 que introduciremos en una matriz */
#define FOREST_SIZE 99
#define true 1
#define false 0

/* Cabeceras */
int visible_from_outside(int** forest, int x, int y);

int count_visible_trees(int** forest) {
    int result = 0, i, j;

    for(i = 0; i < FOREST_SIZE; i++){
        for(j = 0; j < FOREST_SIZE; j++){
            if(visible_from_outside(forest, i, j)){
                result++;
            }
        }
    }
    return result;
}       

int visible_from_outside(int** forest, int x, int y){
    /* Defino resultado para cualquier posible punto cardinal */
    int result_h_1 = true, result_h_2 = true;
    int result_v_1 = true, result_v_2 = true;

    int i, j, actual_tree = -1;
    int tree_size = forest[x][y]; /* Arbol que queremos comprobar si es visible */ 

    /* ----Comprobacion horizontal---- */
    /* IZQUIERDA del arbol */
    for(j = y - 1; j > -1 && result_h_1; j--){
        if(forest[x][j] >= tree_size)
            result_h_1 = false;
    }
    /* DERECHA del arbol */
    for(j = y + 1; j < FOREST_SIZE && result_h_2; j++){
        if(forest[x][j] >= tree_size)
            result_h_2 = false;
    }

    /* ----Comprobacion vertical---- */
    /* ARRIBA del arbol */
    for(i = x - 1; i > -1 && result_v_1; i--){
        if(forest[i][y] >= tree_size)
            result_v_1 = false;
    }
    /* DEBAJO del arbol */
    for(i = x + 1; i < FOREST_SIZE && result_v_2; i++){
        if(forest[i][y] >= tree_size)
            result_v_2 = false;
    }

    return result_h_1 || result_v_1 || result_h_2 || result_v_2;
}


void parse_file(FILE* f, int** forest){
    int i, j;
    char linea[FOREST_SIZE + 1];
    char read;
    for(i = 0; i < FOREST_SIZE; i++){
        fgets(linea, FOREST_SIZE + 2, f);
        linea[strlen(linea)-1] = '\0';
        if(i == 98)
            printf("%s", linea);
        for(j = 0; j < FOREST_SIZE; j++){
            forest[i][j] = linea[j] - '0';
        }
    }
}

void imprimirMatriz(int** matriz) {
    for (int i = 0; i < FOREST_SIZE; i++) {
        for (int j = 0; j < FOREST_SIZE; j++) {
            printf("%d", matriz[i][j]);
        }
        printf("\n");
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


    //imprimirMatriz(forest);
    printf("\n%d", forest[98][0]);

    /* Operacion de cuenta */
    int visible_trees = count_visible_trees(forest);

    /* Imprimir resultado */
    printf("\nArboles visibles: %d\n", visible_trees);

    /* Liberar memoria asignada al bosque */
    for (i = 0; i < FOREST_SIZE; i++) {
        free(forest[i]);
    }
    free(forest);
}