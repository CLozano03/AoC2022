/**
 *  Compilar: gcc Dia04_2.c -o Dia04_2
 *  Ejecutar: Dia04_2.exe input.txt
 */

#include <stdio.h>
#include <stdlib.h>

/* Longitud maxima de una linea */
#define MAX_LINEA 12

/* Funcion que parsea una linea */
void parser_linea(char* linea, int* suma_ol){
    /* Linea del estilo: 2-4,6-8 */
    /* Suponemos que todos los intervalos han sido bien dados */
    int a, b, a_2, b_2;
    sscanf(linea, "%i-%i,%i-%i", &a, &b, &a_2, &b_2);
    /**
     * Ahora sumo a suma_ol si alguno se solapa con otro
     * [2,4] y [3,5] se solapan porque 3 esta entre 2 y 4
     */ 
    if((a <= a_2 && b >= a_2) || (a_2 <= a && b_2 >= a)){
        *suma_ol = *suma_ol + 1;
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
    int suma_ol = 0;

    /* Mientras leo linea, voy procesando programa */
    while(fgets(linea, MAX_LINEA, f)){
        parser_linea(linea, &suma_ol);
    }
    fclose(f);
    
    /* Imprimo resultado */
    printf("Numero de fully contains: %d\n", suma_ol);
    return 0;
}