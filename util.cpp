#include <stdio.h>
#include <string.h>
#include "util.h"

int  nextInstruction(char *Word, int *num1,int *num2)
{
    int  returnV;
    int returnV2;

    fscanf(stdin, "%s", Word);

    if (strcmp(Word, "Stop")==0) return 1; //check if instruction is STOP
    if (strcmp(Word, "PrintADJ")==0) return 1; //check if instruction is Print

    if (strcmp(Word, "SingleSource")==0){ //check if instruction is 
        returnV = fscanf(stdin, "%d", num1); //check if instruction is number is valid
            if (returnV == 1){
                return 1;
            }else{
                return 0;
            }
    }

    if (strcmp(Word, "SinglePair")==0){ //check if instruction is DecreaseKey
        returnV = fscanf(stdin, "%d", num1); //check if number is valid
        returnV2 = fscanf(stdin, "%d", num2); //check if number is valid
        if (returnV == 1 && returnV2 ==1){
            return 1;
        }else{
            return 0;
        }
    }

    if (strcmp(Word, "PrintLength")==0){ //check if instruction is DecreaseKey
        returnV = fscanf(stdin, "%d", num1); //check if number is valid
        returnV2 = fscanf(stdin, "%d", num2); //check if number is valid
        if (returnV == 1 && returnV2 ==1){
            return 1;
        }else{
            return 0;
        }
    }

    if (strcmp(Word, "PrintPath")==0){ //check if instruction is DecreaseKey
        returnV = fscanf(stdin, "%d", num1); //check if number is valid
        returnV2 = fscanf(stdin, "%d", num2); //check if number is valid
        if (returnV == 1 && returnV2 ==1){
            return 1;
        }else{
            return 0;
        }
    }

    return 0;
}
