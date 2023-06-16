/**
 *  Compilar: gcc Dia06_2.c -o Dia06_2
 *  Ejecutar: Dia06_2.exe input.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* MAX_COIN + 1 es el numero de caracteres que no 
tienen que coincidir hasta detectar una marca */
#define MAX_COIN 13 

#define CHECK_KO 0
#define CHECK_OK 1

/* Cabecera de la funcion que me comprueba si los MAX_COIN + 1 caracteres son diferentes */
int check_equals(char* last_chars, char c);

/* Funcion para encontrar el start_marker */
int find_start_marker(FILE* f){
    int i = 0;
    char last_chars[MAX_COIN];
    char c;

    /* Primeros trece caracteres */
    while(i < MAX_COIN){
        c = fgetc(f);
        if(c == EOF){
            fprintf(stderr, "No se ha encontrado el 'start-of-packet marker'.\n");
            exit(1);
        }
        last_chars[i] = c;
        i++;
    }
    
    /* A partir del catorce, ya se puede detectar un start_marker */
    while ((c = fgetc(f)) != EOF) {
        /* Detectamos si los cuatro caracteres mas recientes son diferentes entre si */
        if(check_equals(last_chars, c) == CHECK_OK ){
            return i + 1;
        }
        last_chars[i%MAX_COIN] = c; /* Se va metiendo c en el elemento menos reciente de la lista */
        i++;
    }
    return -1; /* Si ha llegado a este punto, el programa no ha encontrado nada */
}

int check_equals(char* last_chars, char c){
    int i, j;

    /* Comprobamos con el caracter pasado */
    for(i = 0; i < MAX_COIN; i++){
        if(last_chars[i] == c){
            return CHECK_KO;
        }
    }

    /* Comprobamos que todos los caracteres previos de la lista son diferentes */
    for(i = 0; i < MAX_COIN - 1; i++){
        for(j = i + 1; j <= MAX_COIN; j++){
            if(last_chars[i] == last_chars[j]){
                return CHECK_KO;
            }
        }
    }
    return CHECK_OK;
}


/* PROGRAMA PRINCIPAL */
int main(int argc, char* argv[]){
    FILE *f;
    f = fopen(argv[1],"r");
    if (f == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo.\n");
        return 1;
    }

    /* Llamada a la funcion */
    int res = find_start_marker(f);

    /* Devolver la salida */
    fprintf(stdout, "El primer 'start-of-packet marker' esta a partir de: %d", res);

    fclose(f);
    return 0;
}