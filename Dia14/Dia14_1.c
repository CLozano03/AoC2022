/**
 *  Compilar: gcc Dia14_1.c -o Dia14_1
 *  Ejecutar: Dia14_1.exe input.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define GRID_SIZE 1024
#define ROCK '#'
#define SAND '~'
#define AIR '.'

void print_grid(char** grid);

typedef struct _position {
    int x;
    int y;
} Pos;

int fall_sand(char** grid, Pos* pos){
    if(pos-> y == GRID_SIZE - 1){
        return 0;
    } else if(grid[pos->y + 1][pos->x] == AIR){
        grid[pos->y][pos->x] = AIR;
        (pos->y)++;
        grid[pos->y][pos->x] = SAND;
        return fall_sand(grid, pos);
    } else if(grid[pos->y + 1][pos->x - 1] == AIR){
        grid[pos->y][pos->x] = AIR;
        (pos->y)++;
        (pos->x)--;
        grid[pos->y][pos->x] = SAND;
        return fall_sand(grid, pos);
    } else if(grid[pos->y + 1][pos->x + 1] == AIR){
        grid[pos->y][pos->x] = AIR;
        (pos->y)++;
        (pos->x)++;
        grid[pos->y][pos->x] = SAND;
        return fall_sand(grid, pos);
    } else {
        return 1;
    }
}

int count_sand(char** grid){
    int count = 0;
    Pos* ini_pos = malloc(sizeof(Pos));
    ini_pos->x = 500;
    ini_pos->y = 0;

    while(fall_sand(grid, ini_pos) == 1){
        count++;
        ini_pos->x = 500;
        ini_pos->y = 0;
    }

    free(ini_pos);
    return count;
}

void fill_rock(char** grid, Pos* pre, Pos* pos){
    int i;
    
    if(pre->x == pos->x){
        if(pre->y < pos->y){
            for(i = pre->y; i <= pos->y; i++){
                grid[i][pre->x] = ROCK;
            }
        } else {
            for(i = pos->y; i <= pre->y; i++){
                grid[i][pre->x] = ROCK;
            }
        }
    } else {
        if(pre->x < pos->x){
            for(i = pre->x; i <= pos->x; i++){
                grid[pre->y][i] = ROCK;
            }
        } else {
            for(i = pos->x; i <= pre->x; i++){
                grid[pre->y][i] = ROCK;
            }
        }
    }
}

void read_file(FILE* f, char** grid){
    char line[MAX_LINE];
    char* token;
    char* token2;
    int i;
    Pos* pre = malloc(sizeof(Pos));
    Pos* pos = malloc(sizeof(Pos));

    /* Lectura fichero */
    while(fgets(line, MAX_LINE, f)){
        /* Eliminacion salto de linea */
        if(line[strlen(line) - 1] == '\n'){
            line[strlen(line) - 1] = '\0';
        }
        
        pre->x = 0;
        pre->y = 0;

        token = strtok(line, " -> ");

        while (token != NULL){
            sscanf(token, "%d,%d", &pos->x, &pos->y);
            //printf("(%d %d)(%d %d)\n", pre->x, pre->y, pos->x, pos->y);
            
            /* Relleno el grid */
            if(!(pre->x == 0 && pre->y == 0)){
                fill_rock(grid, pre, pos);
            }

            /* Preparo para leer la siguiente coordenada */
            pre->x = pos->x;
            pre->y = pos->y;
            token = strtok(NULL, " -> ");
        }

    }
    fclose(f);
}

void print_grid(char** grid){
    int i, j;
    for(i = 0; i < GRID_SIZE; i++){
        for(j = 0; j < GRID_SIZE; j++){
            if(i == 0 && j == 500){
                printf("%c", '+');
            } else {
                printf("%c", grid[i][j]);
            }
        }
        printf("\n");
    }
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char* argv[]){
    FILE* f; 
    f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    int result, i, j;
    char** grid = (char**)calloc(GRID_SIZE, sizeof(char*)); 
    for(i = 0; i < GRID_SIZE; i++){
        grid[i] = (char*)calloc(GRID_SIZE, sizeof(char));
        for(j = 0; j < GRID_SIZE; j++){
            grid[i][j] = AIR;
        }
    }

    read_file(f, grid);
    result = count_sand(grid);
    //print_grid(grid);


    /* Imprimir el resultado */
    printf("El resultado es: %d\n", result);

    /* Liberar memoria */
    for(i = 0; i < GRID_SIZE; i++){
        free(grid[i]);
    }
    free(grid);

    return 0;
}