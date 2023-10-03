/**
 *  Compilar: gcc Dia07_1.c tree.c -o Dia07_1
 *  Ejecutar: Dia07_1.exe input.txt
 */
#include "tree.h"

#define MAX_READ 32
#define MAX_SIZE 100000
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

long long find_all(dir* current_dir, long long *total_sum){
    int i;
    long long sum_buff = 0;
    long long subdir_sum;

    /* Suma archivos */
    for (i = 0; i < current_dir->num_files; i++) {
        sum_buff += current_dir->files[i]->size;
    }

    i = strcmp(current_dir->name, "/") == 0? 0 : 1;
    /* Suma subdirectorios */
    for (; i < current_dir->num_subdirs; i++) {
        subdir_sum = find_all(current_dir->subdirs[i], total_sum);
        sum_buff += subdir_sum;
    }
    if(sum_buff <= MAX_SIZE){
        *total_sum += sum_buff;
    }   

    return sum_buff;
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

    tree* t = parse_file(f);
    fclose(f);

    /* Buscar todos los ficheros desde la raiz que cumplan la condicion*/
    long long total_sum = 0;
    long long res = find_all(t->root, &total_sum);

    /* Imprimir resultado */
    printf("---------------------------------------------------\n");
    printf("Suma de tamannos de directorios: %lld\n", total_sum);

    /* Liberar memoria */
    free_tree(t->root);
    printf("\nArbol liberado con exito\n");
       
    return 0;
}