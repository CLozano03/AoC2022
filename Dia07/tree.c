#include "tree.h"

dir *mkdir(char *name, dir* current_dir, tree *t) {
    dir *d = malloc(sizeof(dir));
    d->name = malloc(strlen(name) + 1);
    strcpy(d->name, name);
    d->subdirs = NULL;
    d->files = NULL;
    d->num_files = 0;

    /* Si es NULL se trata de la raiz '/' */
    if(current_dir){
        d->num_subdirs = 1; /* No vamos a añadir el directorio '.' en este problema por simplicidad*/
        d->subdirs = malloc(sizeof(dir));
        d->subdirs[0] = current_dir;  
        current_dir->subdirs = realloc(current_dir->subdirs, sizeof(dir) * (current_dir->num_subdirs + 1));
        current_dir->subdirs[current_dir->num_subdirs] = d;
        current_dir->num_subdirs+=1;
    } else {
        /* Configuracion de la raiz */
        d->num_subdirs = 0;
        t->root = d;
    }
    return d;
}

file *touch(char *name, int size, dir* current_dir) {
    file *f = malloc(sizeof(file));
    f->name = malloc(sizeof(char) * strlen(name));
    strcpy(f->name, name);
    f->size = size;
    current_dir->files = realloc(current_dir->files, sizeof(file) * (current_dir->num_files + 1));
    current_dir->files[current_dir->num_files] = f;
    current_dir->num_files+=1;
    return f;
}

dir *cd(char *name, dir* current_dir, tree *t) {
    /* Caso raiz */
    if(strcmp(name, "/") == 0){
        return t->root;
    }

    /* Volver al directorio padre */
    if(strcmp(name, "..") == 0){
        return current_dir->subdirs[0];
    }

    /* Buscar el directorio en el que nos queremos mover */
    int i = strcmp(current_dir->name, "/") == 0 ? 0 : 1;
    for (; i < current_dir->num_subdirs; i++) {
        if(strcmp(current_dir->subdirs[i]->name, name) == 0){
            return current_dir->subdirs[i];
        }
    }
    return NULL;
}

void ls(dir* current_dir) {
    int i;   
    i =strcmp(current_dir->name, "/") == 0? 0 : 1;
    
    /* Imprimir los directorios y ficheros del directorio actual */
    for (; i < current_dir->num_subdirs; i++) {
        if(strcmp(current_dir->name, "/") == 0){
            printf("/%s\t\t\t\tdir\n", current_dir->subdirs[i]->name);
        } else {
            printf("%s/%s\t\t\t\tdir\n", current_dir->name, current_dir->subdirs[i]->name);
        }
    }
    for (i = 0; i < current_dir->num_files; i++) {
        printf("%s\t\t\t\tfile   size=%lld\n", current_dir->files[i]->name, current_dir->files[i]->size);
    }
}

tree *create_tree(){
    /* Creo mi arbol de ficheros, para ello añado primero '/' */
    tree *t = malloc(sizeof(tree));
    dir *root = mkdir("/", NULL, t);
    return t;
}

void free_tree(dir *d){
    int i;
    for (i = 0; i < d->num_files; i++) {
        free(d->files[i]->name);
        free(d->files[i]);
    }
    i = strcmp(d->name, "/") == 0? 0 : 1;
    for (; i < d->num_subdirs; i++) {
        free_tree(d->subdirs[i]);
    }
    //free(d->subdirs);
    //free(d->files);
    free(d->name);
    free(d);
}