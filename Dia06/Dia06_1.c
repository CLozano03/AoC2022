/**
 *  Compilar: gcc Dia06_1.c -o Dia06_1
 *  Ejecutar: Dia06_1.exe input.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COIN 3

int find_start_marker(FILE* f){
    int i = 0;
    char last_3[MAX_COIN];
    char c;

    /* Primeros cuatro caracteres */
    while(i < MAX_COIN){
        c = fgetc(f);
        if(c == EOF){
            fprintf(stderr, "No se ha encontrado el 'start-of-packet marker'.\n");
            exit(1);
        }
        last_3[i] = c;
        i++;
    }
    
    /* A partir del cuarto, ya se puede detectar una */
    while ((c = fgetc(f)) != EOF) {
        /* Detectamos si los cuatro caracteres mas recientes son diferentes entre si */
        if(!(c == last_3[0] || c == last_3[1] || c == last_3[2])){
            /* Antes de retornar, debemos comprobar si alguno de los que habia ya son diferentes entre si */
            if(!(last_3[0] == last_3[1] || last_3[0] == last_3[2] || last_3[1] == last_3[2])){
                return i + 1;
            }
        }
        last_3[i%MAX_COIN] = c; /* Se mete c en el elemento menos reciente de la lista */
        i++;
    }

    return -1; /* Si ha llegado a este punto, el programa no ha encontrado nada */
}



int main(int argc, char* argv[]){
    FILE *f;
    f = fopen(argv[1],"r");
    if (f == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo.\n");
        return 1;
    }

    int res = find_start_marker(f);

    /* Devolver la salida */
    fprintf(stdout, "El primer 'start-of-packet marker' esta a partir de: %d", res);

    fclose(f);
    return 0;
}