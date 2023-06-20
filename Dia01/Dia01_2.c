/**
 *  Compilar: gcc Dia01_2.c -o Dia01_2
 *  Ejecutar: Dia01_2.exe input.txt
 */

#include <stdio.h>
#include <stdlib.h>

#define Max 2048
#define N_ELFOS 3

int min(int* lista) {
    int minimo = lista[0];
    for (int i = 1; i < N_ELFOS; i++) {
        if (lista[i] < minimo) {
            minimo = lista[i];
        }
    }
    return minimo;
}

int main(int argc, char* argv[]){
    FILE *f;
    f = fopen(argv[1],"r");
    if (f == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo.\n");
        return 1;
    }

    /* Variables */
    int cal_elfos[N_ELFOS];
    char linea[2049];
    int cal_elfo_actual = 0;
    int i; 
    int menores_calorias = 0; /* entre los elfos con mas calorias */

    while(fgets(linea, Max, f)){
        if (linea[0] == '\n'){
        /* Cambiamos de elfo */
        /* Comprobamos si es de los que mas calorias tienen */
        menores_calorias = min(cal_elfos);
        if(cal_elfo_actual > menores_calorias){
            /* Buscamos el indice del minimo y lo sustituimos */
            for(i = 0; i < N_ELFOS; i++){
                if(cal_elfos[i] == menores_calorias){
                    cal_elfos[i] = cal_elfo_actual;
                    break;
                }
            }

        }
        cal_elfo_actual = 0; /* Reiniciamos el valor de calorias del elfo a mirar */
        } else{
            cal_elfo_actual += atoi(linea);
        }
    }

    int suma_max = 0;
    /* Sumamos las calorias maximas de los elfos */
    for(i = 0; i < N_ELFOS; i++){
        suma_max += cal_elfos[i];
    }


    fclose(f);
    printf("El numero mayor de calorias es: %i", suma_max);
    return 0;
}