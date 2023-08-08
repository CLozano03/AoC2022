/**
 *  Compilar: gcc Dia10_1.c -o Dia10_1
 *  Ejecutar: Dia10_1.exe input.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_READ 10
#define INITIAL_X 1

int run_instructions(FILE* f){
    char read[MAX_READ];
    int cycle = 1;
    int x = 1;
    int value_to_add;
int signal_strength_sum = 0;

    while(fgets(read, MAX_READ, f)){
        /* Detectamos si se trata de un addx */
        value_to_add = 0; /* Reiniciamos el valor a sumar */
        if(read[0] == 'a'){

            sscanf(read, "addx %d", &value_to_add); /* Cojo el valor a sumar */
            cycle++;
            if(cycle%40 == 20){
                signal_strength_sum += cycle * x;
            }
        }

        cycle++;
        x+= value_to_add;

        /* Detectamos si hay que guardar la intensidad de señal */
        if(cycle%40 == 20){
            signal_strength_sum += cycle * x;
        }
    }
    return signal_strength_sum;
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char* argv[]){
    FILE* f; 
    f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    int signal_strength_sum = run_instructions(f);
    fclose(f);
    
    /* Imprimir resultado */
    printf("\n--------------------------------\nLa fuerza de senial final es: %d\n", signal_strength_sum);

    return 0;
}