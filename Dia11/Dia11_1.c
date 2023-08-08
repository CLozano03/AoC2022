/**
 *  Compilar: gcc Dia11_1.c -o Dia11_1
 *  Ejecutar: Dia11_1.exe input.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MONKEYS 8
#define TAM_LINEA 256
#define ADD 0
#define MUL 1


typedef struct monkey{
    int id;
    int n_items;                    /* Numero de items que tiene el mono */
    int* items;                     /* Array de items que tiene el mono */
    int op[2];                      /*
                                        op[0]: 0 => + ; 1 => -
                                        op[1]: Numero con el que se opera
                                     */
    int divisible_by;               /* Numero por el que puede ser divisible */
    int pos[2];                     /* Monkey to throw => pos[0]: test = true ; pos[1]: test = false */
} Monkey;

void imprimir_mono(Monkey* monkey);

void read_file(FILE *f, Monkey* monkeys){
    char b[TAM_LINEA], buffer_aux[3], b_aux[TAM_LINEA];
    int id  = 0;
    char buff_char;
    int buff_int;
    Monkey* monkey;

    //for(id = 0; id < MONKEYS; id++){
        /* Crear el mono */
        monkey = (Monkey*) malloc(sizeof(Monkey));
        monkey->id = id;

        fgets(b, TAM_LINEA, f); /* Primera linea 'Monkey id:' */

         /* Segunda linea: 'Starting items: ...'*/
        fgets(b, TAM_LINEA, f);
        char *start = strstr(b, ":");
        if (start == NULL) {
            printf("Lista no encontrada.\n");
            exit(0);
        };

        // Utilizamos un bucle while para leer los números hasta el final de la línea
        char* token;

        /* Obtener el primer token */
        token = strtok(start + 1, ", ");
        /* Mientras haya tokens, añadirlos al array */
        while(token != NULL) {
            /* Por cada elemento, añado */
            printf("%s ", token);
            (monkey->n_items)++;
            monkey->items = (int*)realloc(monkey->items, (monkey->n_items + 1) * sizeof(int));
            printf("Hola ");
            monkey->items[monkey->n_items] = atoi(token);
            token = strtok(NULL, ", ");
        }

        //printf("ahfvhwihv\n");

        /* Tercera linea: 'Operation: new = old +/* n' */
        fgets(b, TAM_LINEA, f);
        sscanf(b, "  Operation: new = old %c %d", &buff_char, &buff_int);
        if(buff_char == '+'){
            monkey->op[0] = ADD;
        } else{
            monkey->op[0] = MUL;
        }
        monkey->op[1] = buff_int;

        /* Cuarta linea: ' Test: divisible by 7' */
        fgets(b, TAM_LINEA, f);
        sscanf(b, "  Test: divisible by %d", &buff_int);
        monkey->divisible_by = buff_int;

        /* Quinta y sexta linea: ' Throw: if true => 1 ; if false => 2' */
        fgets(b, TAM_LINEA, f);
        sscanf(b, "    If true: throw to monkey %d", &buff_int);
        monkey->pos[0] = buff_int;
        fgets(b, TAM_LINEA, f);
        sscanf(b, "    If false: throw to monkey %d", &buff_int);
        monkey->pos[1] = buff_int;

        /* Añadir el mono al array */
        monkeys[id] = *monkey;

        /* Leer linea en blanco */
        if(id != MONKEYS - 1){ /* Si no es el ultimo mono, porque habria un EOF */
            fgets(b, TAM_LINEA, f);
            if(b[0] != '\n'){
                printf("Error en el formato del archivo\n");
            }
        }
        exit(0);

        imprimir_mono(monkey);
        printf("\n");
    //}    
}

void imprimir_mono(Monkey* monkey){
    char add_mul;
    printf("Monkey %d:\n", monkey->id);
    printf("Items: ");
    for(int i = 0; i < monkey->n_items; i++){
        printf("%d ", monkey->items[i]);
    }
    if(monkey->op[0] == ADD){
        add_mul = '+';
    } else{
        add_mul = '*';  
    }

    printf("\nOperation: new = old %c %d\n", add_mul, monkey->op[1]);
    printf("Test: divisible by %d\n", monkey->divisible_by);
    printf("Throw: if true => %d; if false => %d\n", monkey->pos[0], monkey->pos[1]);
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

    Monkey* monkeys = (Monkey*) malloc(sizeof(Monkey) * MONKEYS);
    read_file(f, monkeys);
    fclose(f);
    return 0;
}