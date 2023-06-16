/**
 *  Compilar: gcc Dia01_1.c -o Dia01_1
 *  Ejecutar: Dia01_1.exe input.txt
 */

#include <stdio.h>
#include <stdlib.h>

#define Max 2048

int main(int argc, char* argv[]){
    FILE *f;
    f = fopen(argv[1],"r");
    long int max = 0, num, suma = 0;
    char linea[2049];

    while(fgets(linea, Max, f)){
        if (linea[0] == '\n'){
            if(suma > max){
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