/* A for Rock, B for Paper, and C for Scissors */
/* X for Rock, Y for Paper, and Z for Scissors */

int singleRound1(char op, char play){

    if(op == 'A' && play == 'X'){
        return 4;
    }
    else if(op == 'A' && play == 'Y'){
        return 8;
    }
    else if(op == 'A' && play == 'Z'){
        return 3;
    }
    else if(op == 'B' && play == 'X'){
        return 1;
    }
    else if(op == 'B' && play == 'Y'){
        return 5;
    }
    else if(op == 'B' && play == 'Z'){
        return 9;
    }
    else if(op == 'C' && play == 'X'){
        return 7;
    }
    else if(op == 'C' && play == 'Y'){
        return 2;
    }
    else {
        return 6;
    }
}