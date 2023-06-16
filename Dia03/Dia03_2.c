/**
 *  Compilar: gcc Dia03_1.c -o Dia03_1
 *  Ejecutar: Dia03_1.exe input.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 2048

int sum_priorities(FILE* f){
    /* Variables necesarias para el proceso */
    char linea[MAX_LINEA];
    char compartment1[MAX_LINEA/2], compartment2[MAX_LINEA/2];
    char c_in_each;
    int suma_priorities = 0, linea_len, i, j;
    int found;
    
    while(fgets(linea, MAX_LINEA, f)){
        found = 0;
        /* Cada compartment equivale a un substring de la mitad de la linea */ 
        linea_len = strlen(linea);
        strncpy(compartment1, linea, linea_len/2);        
        strncpy(compartment2, linea + linea_len/2, linea_len/2);

        /* Busco el caracter que se repite en ambos compartimentos */
        for(i = 0; i < linea_len/2 && found == 0; i ++){
            for(j = 0; j < linea_len/2 && found == 0; j++){
                if(compartment1[i] == compartment2[j]){
                    c_in_each = compartment1[i];
                    found = 1;
                }
            }
        }
        /* 
            - Lowercase item types a through z have priorities 1 through 26.
            - Uppercase item types A through Z have priorities 27 through 52.
         */
        if (c_in_each >= 'a' && c_in_each <= 'z') {
            suma_priorities += c_in_each - 'a' + 1;
        } else if (c_in_each >= 'A' && c_in_each <= 'Z') {
            suma_priorities += c_in_each - 'A' + 27;
        }
    }
    return suma_priorities;
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
