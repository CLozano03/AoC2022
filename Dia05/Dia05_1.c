/**
 *  Compilar: gcc Dia05_1.c -o Dia05_1
 *  Ejecutar: Dia05_1.exe input.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Longitud maxima de una linea: hay 9 pilas*/
#define MAX_LINEA 128
#define TAM_NODO 3
#define N_STACKS 9

#define FIN_LINEA 0

/* Definimos el tipo nodo */
typedef struct Node {
    char data;
    struct Node* below;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

/* ---------------------------------- */
/* Creo operaciones PUSH y POP */

void push(Stack* stack, char c){
    Node* nodo = (Node*)malloc(sizeof(Node));
    if(nodo == NULL){
        fprintf(stderr, "Error de memoria\n");
        exit(-1);
    }
    nodo -> data = c;
    nodo -> below = stack -> top;
    stack -> top = nodo;
}

Node* pop(Stack* stack){
    Node* aux = stack -> top;
    stack -> top = stack -> top -> below;
    return aux;
}
/* ---------------------------------- */

/*
    Funcion que lee y crea todas las pilas
    del fichero en el array stacks[]
 */
void parse_stacks(FILE *f, Stack* stacks[]){
    char linea[MAX_LINEA];
    Node* nodo_fondo[N_STACKS]; /* Para apuntar al fondo de cada pila */
    Node* aux;
    char c;
    int i;
    
    int desp_linea; /* Variable que me cuenta por donde estoy en la linea */
    int n_stack;    /* Para apuntar al Stack correspondiente */

    /* Inicializar los stacks */
    for(i = 0; i < N_STACKS; i++){
        stacks[i] = (Stack*)malloc(sizeof(Stack));
        if(stacks[i] == NULL){
            fprintf(stderr, "Error de memoria\n");
            exit(-1);
        }
        stacks[i] -> top = NULL;
    }

    while(fgets(linea, MAX_LINEA, f) != NULL){
        /* Inicializar variables de iteracion */
        desp_linea = 0;
        n_stack = 0;

        if(/* linea[0] == ' ' && linea[1] == '1'*/ linea[0] != '['){
            break; /* Acabamos las pilas */
        }

        /* Recorremos la linea */
        while(n_stack < N_STACKS){
            c = linea[desp_linea + 1]; 
            if(c == ' '){
                /* Si es un espacio, saltamos */
                desp_linea += TAM_NODO + 1; /* +1 para saltar el espacio */
                n_stack++;
                continue;
            }
            
            aux = (Node*)malloc(sizeof(Node));
            if(aux == NULL){
                fprintf(stderr, "Error de memoria\n");
                exit(-1);
            }
            aux->data = c;
            aux->below = NULL;

                
            if(stacks[n_stack] -> top == NULL){
                /* Si la pila esta vacia, creamos el nodo fondo */
                nodo_fondo[n_stack] = aux;
                if(nodo_fondo[n_stack] == NULL){
                    fprintf(stderr, "Error de memoria\n");
                    exit(-1);
                }
                stacks[n_stack] -> top = nodo_fondo[n_stack];

            } else {
                /* Si la pila no esta vacia, creamos el nodo y lo metemos en la pila */
                nodo_fondo[n_stack] -> below = aux;
                nodo_fondo[n_stack] = aux;
            }

            desp_linea += TAM_NODO + 1; /* +1 para saltar el espacio */
            n_stack++;
            
        }
    }

    /* Leer la linea en blanco*/
    fgets(linea, MAX_LINEA, f);
}    


/* Metodo para ejecutar los movimientos */
void parse_movements(FILE *f, Stack* stacks[]){
    char linea[MAX_LINEA];
    Node* aux;
    int i, n, st_ini, st_fin;

    /* leer hasta el final del archivo */
    while(fgets(linea, MAX_LINEA, f) != NULL){
        sscanf(linea, "move %d from %d to %d", &n, &st_ini, &st_fin);
        /* Corregir para las operaciones de pila */
        st_ini--;
        st_fin--;

        /* Repetimos n veces mover el nodo top de la pila al top de la otra pila */
        for(i = 0; i < n; i++){
            /* Sacar nodo de la pila st_ini y meterlo en la st_fin*/
            push(stacks[st_fin], pop(stacks[st_ini]) -> data);        
        }
    }
}

void print_result(Stack* stacks[]){
    int i;
    char c;
    char result[N_STACKS];

    printf("\nEl resultado final es: ");
    for(i = 0; i < N_STACKS; i++){
        c = stacks[i]->top->data;
        printf("%c", c);
    }

    printf("\n");
}

/* Funcion para liberar la memoria dinamica usada por los stacks */
int free_stacks(Stack* stacks){
    int i;
    Node* aux, *aux2;
    
    for(i = 0; i < 9; i++){
        aux = stacks[i].top;
        while(aux != NULL){
            aux2 = aux;
            aux = aux->below;
            free(aux2);
        }
    }
    return 0;
}


/* PROGRAMA PRINCIPAL */
int main(int argc, char* argv[]){
    /* Variables del programa */
    FILE *f;
    Stack* stacks[N_STACKS];

    f = fopen(argv[1],"r");
    if(f == NULL){
        printf("Error al abrir fichero\n");
        return 1;
    }

    /* Lectura fchero y ejecucion de movimientos */
    parse_stacks(f, stacks);
    parse_movements(f, stacks);
    /* Contamos resultado */
    print_result(stacks);
    fclose(f);

    /* Liberar memoria dinamica */
    printf("Free Stacks: %d", free_stacks(stacks[0]));
    return 0;
}