/**
 *  Compilar: gcc Dia05_1.c -o Dia05_1
 *  Ejecutar: Dia05_1.exe input.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Longitud maxima de una linea: hay 9 pilas*/
#define MAX_LINEA 64
#define TAM_NODO 3
#define N_STACKS 9

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
void print_stack(Stack* stacks[], int i){

    Node* aux = stacks[i] -> top;
    while(aux != NULL){
        printf("%c ", aux -> data);
        aux = aux -> below;
    }
    printf("\n");   
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

/* void free_stacks(Stack* stacks){
    int i;
    Node* aux, aux2;
    for(i = 0; i < 9; i++){
        aux = stacks[i].top;
        while(aux != NULL){
            aux2 = aux;
            aux = aux -> below;
            free(aux2);
        }
    }
} */


/* PROGRAMA PRINCIPAL */
int main(int argc, char* argv[]){
    FILE *f;
    f = fopen(argv[1],"r");
    if(f == NULL){
        printf("Error al abrir fichero\n");
        return 1;
    }

    char linea[MAX_LINEA];
    char nodo_str[TAM_NODO + 1];
    Node* nodo_fondo[N_STACKS]; /* Para apuntar al fondo de cada pila */
    Node* aux;
    int i;
    int desp_linea; /* Variable que me cuenta por donde estoy en la linea */
    int n_stack;    /* Para apuntar al Stack correspondiente */

    /* Inicializar los stacks */
    Stack* stacks[N_STACKS];
    for(i = 0; i < N_STACKS; i++){
        stacks[i] = (Stack*)malloc(sizeof(Stack));
        if(stacks[i] == NULL){
            fprintf(stderr, "Error de memoria\n");
            exit(-1);
        }
        stacks[i] -> top = NULL;
    }

    /* Leemos el fichero linea a linea */
    while(fgets(linea, MAX_LINEA, f) != NULL){
        desp_linea = 0;
        n_stack = 0;

        if(linea[0] != '['){
            printf("El resultado final es: ");
            /* for(i = 0; i < N_STACKS; i++){
                printf("%c", stacks[i]->top->data);
            } */ 
            printf("\n");
            break;
        }

        /* Leemos la linea caracter a caracter */
        while(n_stack < N_STACKS){

            if(linea[desp_linea + 1] == ' '){
                /* Si el caracter es un espacio, pasamos al siguiente */
                desp_linea+= TAM_NODO + 1;
                n_stack++;
                continue;
            }
            printf("%c ", linea[desp_linea + 1]);
            
            nodo_fondo[n_stack] = (Node*)malloc(sizeof(Node));
            if(stacks[n_stack] -> top == NULL){
                /* Si la pila esta vacia, creamos el nodo fondo */
                if(nodo_fondo[n_stack] == NULL){
                    fprintf(stderr, "Error de memoria\n");
                    exit(-1);
                }
                nodo_fondo[n_stack] -> data =linea[desp_linea + 1];
                nodo_fondo[n_stack] -> below = NULL;
                stacks[n_stack] -> top = nodo_fondo[n_stack];
            } else {
                /* Si la pila no esta vacia, creamos el nodo y lo metemos en la pila */
                nodo_fondo[n_stack] -> below = (Node*)malloc(sizeof(Node));
                if(nodo_fondo[n_stack] -> below == NULL){
                    fprintf(stderr, "Error de memoria\n");
                    exit(-1);
                }
                nodo_fondo[n_stack] -> data = linea[desp_linea + 1];
                nodo_fondo[n_stack] -> below = NULL;
            }

            desp_linea += TAM_NODO + 1;
            n_stack++;
        }
        printf("\n");
    }

    /* Stack* stacks[N_STACKS];
    parse_stacks(f, stacks); */
    //print_stack(stacks, 1);
    /* parse_movements(f);
    /* Contamos resultado */
    //print_stack(stacks, 0);
    //print_result(stacks);
    fclose(f);
    /* free_stacks(stacks) */
}