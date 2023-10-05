/**
 *  Compilar: gcc Dia07_2.c tree.c -o Dia07_2
 *  Ejecutar: Dia07_2.exe input.txt
 */
#include "tree.h"

#define MAX_READ 32
#define MAX_SPACE 70000000
#define UNUSED_NEED 30000000
/* ---------------------------------------------------------------------------------------- */
/* Funcion de procesado del archivo */
tree *parse_file(FILE *f){
    /* Variables auxiliares */
    char read[MAX_READ + 1];
    int n_campo, leidas = 0, buff_size;
    char *token;
    char dir_new[MAX_READ + 1];
    char file_new[MAX_READ + 1];
    
    tree *t = create_tree();
    dir *current_dir = NULL;

    /* PROCESADO DEL FICHERO */
    while(fgets(read, MAX_READ, f)){
        /* Elimino el salto de linea */
        if(read[strlen(read) - 1] == '\n')
            read[strlen(read) - 1] = '\0';

        if(read[0] == '$'){
            /* Es un comando */

            if(read[2] == 'c'){
                /* Comando cd */
                token = strtok(read, " ");
                n_campo = 1;

                /* Busco el directorio objetivo */
                while(token != NULL){
                    if(n_campo == 3){
                        strcpy(dir_new,token);
                        break;
                    }
                    token = strtok(NULL, " ");
                    n_campo++;
                }

                /* Ejecuto comando */
                current_dir = cd(dir_new, current_dir, t);
            } else if(read[2] == 'l')
                /* Comando ls */{
            } else {
                fprintf(stderr, "Comando no reconocido\n");
                exit(1);
            }
        } else {
            if(read[0] == 'd'){
                /* Creacion de un nuevo directorio */
                sscanf(read, "dir %s", &dir_new);
                mkdir(dir_new, current_dir, t);
            } else {
                /* Creacion de un nuevo fichero */
                sscanf(read, "%lld %s", &buff_size, file_new);
                touch(file_new, buff_size, current_dir);
            }
        }
        leidas++;
    }
    
    printf("Fin de la lectura del archivo. Lineas leidas: %d\n", leidas);
    
    return t;
}

long long dir_size(dir* current_dir){
    int i;
    long long sum_buff = 0;

    /* Suma archivos */
    for (i = 0; i < current_dir->num_files; i++) {
        sum_buff += current_dir->files[i]->size;
    }

    i = strcmp(current_dir->name, "/") == 0? 0 : 1;
    /* Suma subdirectorios */
    for (; i < current_dir->num_subdirs; i++) {
        sum_buff += dir_size(current_dir->subdirs[i]);
    }
    return sum_buff;
}

void solve_aux(dir* current_dir, long long *min_free_needed, long long *free_needed){
    long long aux, dir_s;
    int i = strcmp(current_dir->name, "/") == 0? 0 : 1;

    for(i; i < current_dir->num_subdirs; i++){
        dir_s= dir_size(current_dir->subdirs[i]);
        if(dir_s >= *free_needed && dir_s <= *min_free_needed){
            *min_free_needed = dir_s;
        }
        solve_aux(current_dir->subdirs[i], min_free_needed, free_needed);
    }   
}

long long solve(tree *t){
    /* Tamaño ocupado por nuestro sistema de ficheros */
    long long space_used;
    space_used = dir_size(t->root);

    long long unused_space = MAX_SPACE - space_used;
    long long free_needed = UNUSED_NEED - unused_space;

    long long min_free_needed = MAX_SPACE; /* Inicializo a valor alto para evitar bugs */
    long long aux;

    /* Busco recursivamente el directorio que, cuando lo libero consigo al menos el free_needed pero que es minimo */
    solve_aux(t->root, &min_free_needed, &free_needed);

    return min_free_needed;
}

/* ---------------------------------------------------------------------------------------- */
/* PROGRAMA PRINCIPAL */
int main(int argc, char* argv[]){
    FILE *f;
    f = fopen(argv[1],"r");
    if (f == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo.\n");
        return 1;
    }

    /* Lectura de fichero */
    tree* t = parse_file(f);
    fclose(f);


    long long size_liberar = solve(t);
    
    /* Imprimir resultado */
    printf("---------------------------------------------------\n");
    printf("Tamanno de directorio a eliminar: %lld\n", size_liberar);

    /* Liberar memoria */
    free_tree(t->root);
    printf("\nArbol liberado con exito\n");
       
    return 0;
}