/**
 *  Compilar: gcc Dia04_1.c -o Dia04_1
 *  Ejecutar: Dia04_1.exe input.txt
 */

#include <stdio.h>
#include <stdlib.h>

/* Longitud maxima de una linea */
#define MAX_LINEA 12

/* Funcion que parsea una linea */
void parser_linea(char* linea, int* suma_fc){
    /* Linea del estilo: 2-4,6-8 */
    /* Suponemos que todos los intervalos han sido bien dados */
    int a, b, a_2, b_2;
    sscanf(linea, "%i-%i,%i-%i", &a, &b, &a_2, &b_2);
    /**
     * Compruebo si algun intervalo [a,b] ó [a_2, b_2] pertenece a otro 
     * en ese caso sumo 1 a suma_fc 
     */ 
    if((a <= a_2 && b >= b_2) || (a_2 <= a && b_2 >= b)){
        *suma_fc = *suma_fc + 1;
    }
}

/**
 * PROGRAMA PRINCIPAL
 * Lee fichero y llama a funcion parser_linea
 */
int main(int argc, char* argv[]){
    /* Abro fichero */
    FILE *f;
    f = fopen(argv[1],"r");

    if(f == NULL){
        printf("Error al abrir fichero\n");
        return 1;
    }

    /* String de Parseo y suma */
    char linea[MAX_LINEA];
    int suma_fc = 0;

    /* Mientras leo linea, voy procesando programa */
    while(fgets(linea, MAX_LINEA, f)){
        parser_linea(linea, &suma_fc);
    }
    fclose(f);
    
    /* Imprimo resultado */
    printf("Numero de fully contains: %li\n", suma_fc);
    return 0;
}