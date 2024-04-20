// Name: Shaashvat Mittal
// ASUID: 1224208336
// Description: util.cpp contains utility function for the program flow. It check for the
// user input commands and returns 1 if true and 0 if false/wrong.

#include <stdio.h>
#include <string.h>
#include "util.h"
#include "math.h"

// implementation of the nextInstruction Function.
int  nextInstruction(char *Word, int *num1,int *num2)
{
    int  returnV;
    int returnV2;

    // user input
    fscanf(stdin, "%s", Word);

    // Checking for correct inputs.
    // checking for Stop input.
    if (strcmp(Word, "Stop")==0) return 1;

    // checking for PrintADJ input
    if (strcmp(Word, "PrintADJ")==0) return 1;

    // checking for single source input.
    if (strcmp(Word, "SingleSource")==0)
    { 
        // check if valid number or not.
        returnV = fscanf(stdin, "%d", num1); 

        // if yes then return 1.
        if (returnV == 1)
        {
            return 1;
        }
    }

    // checking for single pair.
    if (strcmp(Word, "SinglePair")==0)
    { 
        // checking if both the numbers are valid or not.
        returnV = fscanf(stdin, "%d", num1); 
        returnV2 = fscanf(stdin, "%d", num2); 

        // if yes then return 1.
        if (returnV == 1 && returnV2 ==1)
        {
            return 1;
        }
    }

    // cheking for print length.
    if (strcmp(Word, "PrintLength")==0)
    { 
        // cheking if both the numbers are valid or not.
        returnV = fscanf(stdin, "%d", num1); 
        returnV2 = fscanf(stdin, "%d", num2); 

        // if yes then return 1.
        if (returnV == 1 && returnV2 ==1)
        {
            return 1;
        }
    }

    // checking for print path.
    if (strcmp(Word, "PrintPath")==0)
    { 
        // checking is both the numbers are valid or not.
        returnV = fscanf(stdin, "%d", num1); 
        returnV2 = fscanf(stdin, "%d", num2); 

        // if yes then return 1.
        if (returnV == 1 && returnV2 ==1)
        {
            return 1;
        }
    }
    return 0;
}