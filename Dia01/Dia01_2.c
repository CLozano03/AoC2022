/**
 *  Compilar: gcc Dia01_2.c -o Dia01_2
 *  Ejecutar: Dia01_2.exe input.txt
 */

#include <stdio.h>
#include <stdlib.h>

#define Max 2048

int main(int argc, char* argv[]){
    FILE *f;
    f = fopen(argv[1],"r");
    long int max[3] = {0, 1, 2};
    long int num, suma = 0;
    int i = 0;
    int indiceMinimo;
    char linea[2049];

    while(fgets(linea, Max, f)){
        if (linea[0] == '\n'){
            if(i < 3){
            max[i] = suma;
            i++;
            continue;
            }
            /* Calcular el minimo */
            if(suma > min(max)){
                max = suma;
            }
            suma = 0;
        } else{
            num = atoi(linea);
            suma = suma + num;
        }
    }
    fclose(f);
    printf("El numero mayor de calorias es: %li", max);
    return 0;
}