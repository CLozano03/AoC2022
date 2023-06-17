#include <stdio.h>
#include <stdlib.h>

#include "round1.h"
#include "round2.h"

#define LINEA_MAX 10

int executeGame(FILE * file){
    int resultadoJuego = 0;
    char linea[LINEA_MAX];


    while(fgets(linea, LINEA_MAX, file)){
        /* resultadoJuego += singleRound1(linea[0], linea[2]); */
        /* resultadoJuego += singleRound2(linea[0], linea[2]);  */
    }
 
    return resultadoJuego;
}