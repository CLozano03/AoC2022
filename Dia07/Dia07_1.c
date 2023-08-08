/**
 *  Compilar: gcc Dia07_1.c -o Dia07_1
 *  Ejecutar: Dia07_1.exe input.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*  */
/* 
- / (dir)
  - a (dir)
    - e (dir)
      - i (file, size=584)
    - f (file, size=29116)
    - g (file, size=2557)
    - h.lst (file, size=62596)
  - b.txt (file, size=14848514)
  - c.dat (file, size=8504156)
  - d (dir)
    - j (file, size=4060174)
    - d.log (file, size=8033020)
    - d.ext (file, size=5626152)
    - k (file, size=7214296)
 */
/* ---------------------------------------------------------------------------------------- */
/* Defino mis estructuras que me permiten crear un arbol combinando todas ellas */
typedef struct _file {
    char *name;
    int size;
} file;

typedef struct _dir {
    char *name;
    struct _dir *subdirs[];
    struct _file *files[];
} dir;

typedef struct _tree {
    struct _dir *root;
} tree;

/* ---------------------------------------------------------------------------------------- */
/* Funciones para crear y destruir los elementos de mi arbol */
dir *create_dir(char *name) {
    dir *d = malloc(sizeof(dir));
    d->name = malloc(sizeof(char) * strlen(name));
    strcpy(d->name, name);
    d->subdirs = NULL;
    d->files = NULL;
    return d;
}

file *create_file(char *name, int size) {
    file *f = malloc(sizeof(file));
    f->name = malloc(sizeof(char) * strlen(name));
    strcpy(f->name, name);
    f->size = size;
    return f;
}

/* ---------------------------------------------------------------------------------------- */
/* Funciones para agregar elementos a mi arbol */
void add_dir(dir* d, dir* subdir) {
    if (d->subdirs == NULL) {
        d->subdirs = malloc(sizeof(dir));
        d->subdirs = subdir;
    } else {
        dir *aux = d->subdirs;
        while (aux->subdirs != NULL) {
            aux = aux->subdirs;
        }
        aux->subdirs = malloc(sizeof(dir));
        aux->subdirs = subdir;
    }
}
/* ---------------------------------------------------------------------------------------- */
/* Funcion de procesado del archivo, mientras suma los tamaños de los ficheros*/
int create_tree(FILE* f, ){

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

    /* int res = find_start_marker(f);

    /* Devolver la salida
    fprintf(stdout, "El primer 'start-of-packet marker' esta a partir de: %d", res); */

    fclose(f);
    return 0;
}