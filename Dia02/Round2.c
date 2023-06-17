/* X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win */

int singleRound2(char op, char res){

    if(op == 'A' && res == 'X'){
        return 0+3;
    }
    else if(op == 'A' && res == 'Y'){
        return 3+1;
    }
    else if(op == 'A' && res == 'Z'){
        return 6+2;
    }
    else if(op == 'B' && res == 'X'){
        return 0+1;
    }
    else if(op == 'B' && res == 'Y'){
        return 3+2;
    }
    else if(op == 'B' && res == 'Z'){
        return 6+3;
    }
    else if(op == 'C' && res == 'X'){
        return 0+2;
    }
    else if(op == 'C' && res == 'Y'){
        return 3+3;
    }
    else {
        return 6+1;
    }
}