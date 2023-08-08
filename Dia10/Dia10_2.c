/**
 *  Compilar: gcc Dia10_2.c -o Dia10_2
 *  Ejecutar: Dia10_2.exe input.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_READ 10
#define INITIAL_X 1

void run_instructions(FILE* f){
    char read[MAX_READ];
    int cycle = 0, value_to_add;
    int x = INITIAL_X;

    /* Lectura fichero */
    while(fgets(read, MAX_READ, f)){
        value_to_add = 0;

        /* Detectamos si se trata de un addx */
        if(read[0] == 'a'){

            sscanf(read, "addx %d", &value_to_add);
            if(x == cycle|| x - 1 == cycle|| x + 1 == cycle){
                printf("#");
            } else {
                printf(".");
            }

            cycle++;
            /* Comprobar si salto de linea */
            if(cycle%40 == 0){
                printf("\n");
                cycle %= 40;
            }
        }

        if(x == cycle|| x - 1 == cycle|| x + 1 == cycle){
                printf("#");
        } else {
                printf(".");
        }

        cycle++;
        x+= value_to_add;

        /* Comprobar si salto de linea */
        if(cycle%40== 0){
            printf("\n");
            cycle %= 40;
        }
    }
    printf("\n");
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char* argv[]){
    FILE* f; 
    f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    run_instructions(f);
    fclose(f);

    return 0;
}