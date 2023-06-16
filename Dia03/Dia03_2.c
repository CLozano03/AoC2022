/**
 *  Compilar: gcc Dia03_2.c -o Dia03_2
 *  Ejecutar: Dia03_2.exe input.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 1024

int sum_priorities(FILE* f){
    /* Variables necesarias para el proceso */
    char linea1[MAX_LINEA], linea2[MAX_LINEA], linea3[MAX_LINEA];
    char c_in_all;
    int suma_item_types = 0, linea1_len, linea2_len, linea3_len, i, j, k;
    int found;
    
    /* Se asume por el enunciado que el archivo input tiene un numero de lineas multiplo de 3 */
    while(fgets(linea1, MAX_LINEA, f)){
        fgets(linea2, MAX_LINEA, f);
        fgets(linea3, MAX_LINEA, f);
        found = 0;
        /* Cada compartment equivale a un substring de la mitad de la linea */ 
        linea1_len = strlen(linea1);
        linea2_len = strlen(linea2);
        linea3_len = strlen(linea3);

        /* Busco el caracter que se repite en ambos compartimentos */
        for(i = 0; i < linea1_len && found == 0; i ++){
            for(j = 0; j < linea2_len && found == 0; j++){
                if(linea1[i] == linea2[j]){
                    c_in_all = linea1[i];
                    for(k = 0; k < linea3_len && found == 0; k++){
                        if(c_in_all == linea3[k])
                            found = 1;
                    }
                }
            }
        }
        /* 
            Asigno las prioridades a los item types:
            - Lowercase item types a through z have priorities 1 through 26.
            - Uppercase item types A through Z have priorities 27 through 52.
         */
        if (c_in_all >= 'a' && c_in_all <= 'z') {
            suma_item_types += c_in_all - 'a' + 1;
        } else if (c_in_all >= 'A' && c_in_all <= 'Z') {
            suma_item_types += c_in_all - 'A' + 27;
        }
    }
    return suma_item_types;
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char* argv[]){
    /* Abro fichero */
    FILE *f;
    f = fopen(argv[1],"r");

    if(f == NULL){
        printf("Error al abrir fichero\n");
        return 1;
    }

    /* Obtengo resultado */
    int priorities = sum_priorities(f);
    
    /* Imprimo resultado */
    printf("La suma de priorities: %i\n", priorities);
    return 0;
}
