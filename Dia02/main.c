#include <stdio.h>

#include "RPScissors.h"

int main(int argc, char* argv[]){
    
    if(argc != 1){
        printf("Error, introduce un unico argumento\n");
        return -1;
    }

    int totalPoints = executeGame(fopen(argv[1],"r"));
    
    printf("Total points: %d\n", totalPoints);
    
    return 0;
}