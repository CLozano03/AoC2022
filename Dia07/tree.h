#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estructuras que me permiten crear un arbol combinando todas ellas */
typedef struct _file {
    char *name;
    long long size;
} file;

/* OJO! subdirs[0] sera el directorio padre ".." salvo caso de la raiz */
typedef struct _dir {
    char *name;
    int num_subdirs;
    int num_files;
    struct _file **files;
    struct _dir **subdirs;
} dir;

typedef struct _tree {
    struct _dir *root;
} tree;

/* -------------Metodo------------- */

/* Creacion directorio */
dir *mkdir(char *name, dir* current_dir, tree *t);

/* Creacion fichero */
file *touch(char *name, int size, dir* current_dir);

/* Cambio de directorio */
dir *cd(char *name, dir* current_dir, tree *t);

/* Listar directorio */
void ls(dir* current_dir);

/* Inicializacion del arbol */
tree *create_tree();

/* borra recursivamente un directorio */
void free_tree(dir *d);