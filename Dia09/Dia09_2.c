/**
 *  Compilar: gcc Dia09_2.c -o Dia09_2
 *  Ejecutar: Dia09_2.exe input.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 512
#define VISITED '#'
#define INITIAL_POS GRID_SIZE/2
#define NUMBER_TAIL 9

typedef struct _position {
    int x;
    int y;
} Pos;

void print_snake(Pos* a_pos[]);

/**
 * @brief Se pretende ajustar la cola en la cuadricula tras haber movido la cabeza
 * 
 * @param grid 
 * @param head 
 * @param tail 
 * @return 1 si la cola esta visitando una posicion nueva. 0 en otro caso
 */
int adjust_tail(char** grid, Pos* head, Pos* tail, Pos* a_pos[], int number){
    /* the head (H) and tail (T) must always be touching
    (diagonally adjacent and even overlapping both count as touching) */

    /* Primero extraemos las coordenadas para comparar */
    int* h_x = &head->x;
    int* h_y = &head->y;
    int* t_x = &tail->x;
    int* t_y = &tail->y;

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
    } else if ((*t_x + 1 == *h_x && *t_y + 2 == *h_y) || (*t_x + 2 == *h_x && *t_y + 1 == *h_y) || (*t_x + 2 == *h_x && *t_y + 2 == *h_y)){
        (*t_x)++;
        (*t_y)++;
    /* Arriba Derecha */
    } else if ((*t_x + 2 == *h_x && *t_y - 1 == *h_y) || (*t_x + 1 == *h_x && *t_y - 2 == *h_y) || (*t_x + 2 == *h_x && *t_y - 2 == *h_y)){
        (*t_x)++;
        (*t_y)--;
    /* Abajo Derecha */
    } else if ((*t_x - 1 == *h_x && *t_y - 2 == *h_y) || (*t_x - 2 == *h_x && *t_y - 1 == *h_y) || (*t_x - 2 == *h_x && *t_y - 2 == *h_y)){
        (*t_x)--;
        (*t_y)--;
    /* Abajo Izquierda */
    } else if((*t_x - 2 == *h_x && *t_y + 1 == *h_y) || (*t_x - 1 == *h_x && *t_y + 2 == *h_y) || (*t_x - 2 == *h_x && *t_y + 2 == *h_y)){
        (*t_x)--;
        (*t_y)++;
    }

    /* --------------- */
    /* Finalmente comprobamos si era una posicion visitada por lo que en el grid habia un '#' */
    /* En otro caso estariamos sumando varias veces una misma posicion visitada */
    if(number == NUMBER_TAIL){
        if(grid[*t_x][*t_y] != VISITED){
            grid[*t_x][*t_y] = VISITED;
            return 1;
        }
        return 0;
    }
     
    /* Si no es la cola llamamos al siguiente elemento */
    return adjust_tail(grid, a_pos[number], a_pos[number + 1], a_pos, number + 1);   
}

int move_head(char** grid, Pos* head, Pos* a_pos[], char dir, int step){
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
        count += adjust_tail(grid, head, a_pos[1], a_pos, 1);
    }
    return count;
}

int read_file(FILE* f, char** grid){
    char dir;
    int step, i, result = 0;

    Pos* a_pos[NUMBER_TAIL + 1];

    /* Creamos nuestras coordenadas para la cola y la cabeza */
    for(i = 0; i < NUMBER_TAIL + 1; i++){
        Pos* pos = malloc(sizeof(Pos));
        pos->x = INITIAL_POS;
        pos->y = INITIAL_POS;
        a_pos[i] = pos;
    }

    Pos* head = a_pos[0];

    printf("Posicion head inicial: (%d, %d)\n", head->x, head->y);

    /* Leemos fichero */
    while(fscanf(f, "%c %d ", &dir, &step) != EOF){
        result += move_head(grid, head, a_pos, dir, step);
    }
    fclose(f);

    return result;
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char* argv[]){
    FILE* f; 
    f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    int res, i;
    char** grid = (char**)calloc(GRID_SIZE, sizeof(char*)); 
    for(i = 0; i < GRID_SIZE; i++){
        grid[i] = (char*)calloc(GRID_SIZE, sizeof(char));
    }
    res = read_file(f, grid);

    /* Imprimir resultado */
    printf("\n--------------------------------\nNumero de lugares visitados: %d", res);

    /* Liberar memoria */
    for(i = 0; i < GRID_SIZE; i++){
        free(grid[i]);
    }
    free(grid);

    return 0;
}