/**
 *  Compilar: gcc Dia09_1.c -o Dia09_1
 *  Ejecutar: Dia09_1.exe input.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 512
#define VISITED '#'
#define INITIAL_POS GRID_SIZE/2

typedef struct _position {
    int x;
    int y;
} Pos;

/**
 * @brief Se pretende ajustar la cola en la cuadricula tras haber movido la cabeza
 * 
 * @param grid 
 * @param head 
 * @param tail 
 * @return 1 si la cola esta visitando una posicion nueva. 0 en otro caso
 */
int adjust_tail(char** grid,Pos* head, Pos* tail){
    /* the head (H) and tail (T) must always be touching
    (diagonally adjacent and even overlapping both count as touching) */

    /* Primero extraemos las coordenadas para comparar */
    int* h_x = &head->x;
    int* h_y = &head->y;
    int* t_x = &tail->x;
    int* t_y = &tail->y;

    /* Marcamos como visitada la posicion en el grid */
    grid[*t_x][*t_y] = VISITED;

    /* -----AJUSTAMOS POSICION DE LA COLA------ */
    /* Estan en la misma fila */
    if(*h_x == *t_x){
        if(*h_y == *t_y + 2){
            (*t_y)++;
        } else if (*h_y == *t_y - 2) {
            (*t_y)--; 
        }
    /* Estan en misma columna */
    } else if(*t_y == *h_y){
        if(*t_x + 2 == *h_x){
            (*t_x)++;
        } else if (*t_x - 2 == *h_x){
            (*t_x)--; 
        }
    /* DIAGONAL -> 4 CASOS*/
    /* Arriba Izquierda */
    } else if ((*t_x + 1 == *h_x && *t_y + 2 == *h_y) || (*t_x + 2 == *h_x && *t_y + 1 == *h_y)){
        (*t_x)++;
        (*t_y)++;
    /* Arriba Derecha */
    } else if ((*t_x + 2 == *h_x && *t_y - 1 == *h_y) || (*t_x + 1 == *h_x && *t_y - 2 == *h_y)){
        (*t_x)++;
        (*t_y)--;
    /* Abajo Derecha */
    } else if ((*t_x - 1 == *h_x && *t_y - 2 == *h_y) || (*t_x - 2 == *h_x && *t_y - 1 == *h_y)){
        (*t_x)--;
        (*t_y)--;
    /* Abajo Izquierda */
    } else if((*t_x - 2 == *h_x && *t_y + 1 == *h_y) || (*t_x - 1 == *h_x && *t_y + 2 == *h_y)){
        (*t_x)--;
        (*t_y)++;
    }

    /* --------------- */
    /* Finalmente comprobamos si era una posicion visitada por lo que en el grid habia un '#' */
    /* En otro caso estariamos sumando varias veces una misma posicion visitada */
    if(grid[*t_x][*t_y] != VISITED){
        return 1;
    }
    return 0;
}

int move_head(char** grid, Pos* head, Pos* tail, char dir, int step){
    int i;
    int count = 0;

    for(i = 0; i < step; i++){
        switch(dir){
            case 'L':
                head->y = head->y - 1;
                break;
            case 'R':
                head->y = head->y + 1;
                break;
            case 'U':
                head->x = head->x - 1;
                break;
            case 'D':
                head->x = head->x + 1;
                break;
        }
    /* Ajustamos la cola */
    count += adjust_tail(grid, head, tail); 
    }
    return count;
}

void read_file(FILE* f, char** grid, int* result){
    char dir;
    int step;

    /* Creamos nuestras coordenadas para la cola y la cabeza */
    Pos* head = malloc(sizeof(Pos));
    head->x = INITIAL_POS;
    head->y = INITIAL_POS;

    Pos* tail = malloc(sizeof(Pos));
    tail->x = INITIAL_POS; /* Empiezan en el mismo lugar */
    tail->y = INITIAL_POS;

    printf("Posicion head inicial: %d\n", head->x);

    /* Leemos fichero */
    while(fscanf(f, "%c %d ", &dir, &step) != EOF){
        *result += move_head(grid, head, tail, dir, step);
    }
    fclose(f);
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char* argv[]){
    FILE* f; 
    f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    int result = 0, i;
    char** grid = (char**)calloc(GRID_SIZE, sizeof(char*)); 
    for(i = 0; i < GRID_SIZE; i++){
        grid[i] = (char*)calloc(GRID_SIZE, sizeof(char));
    }
    read_file(f, grid, &result);
    result++; /* Sumamos 1 porque la posicion final tambien cuenta */

    /* Imprimir resultado */
    printf("\n--------------------------------\nNumero de lugares visitados: %d", result);

    /* Liberar memoria */
    for(i = 0; i < GRID_SIZE; i++){
        free(grid[i]);
    }
    free(grid);

    return 0;
}