// a simple assembler for our 8-bit stack machine

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>

#include "isa.h"
#define INST_SIZE 8

int main(int argc, char **argv) {
    FILE *fbin;
    char op;
    char operand;
    unsigned char inst;
    char stack[32];
    int tos = -1;

    if (argc < 2) {
        printf("Usage: ./interpret prog.bin\n");
        exit(1);
    }

    fbin = fopen(argv[1],"r");
    if (fbin == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // read each one byte instruction from the binary file
    while (fread(&inst,1,1,fbin) != 0) {


// write your code here to decode the instructions
// for the simple stack machine
// Hint: First get the operation and the operand
// then perform the corrsponding operation

      
// Sample output for OUT instruction:

      if (tos < 0)
	printf("TOS = empty\n");
      else
	printf("TOS = %d\n",stack[tos]);

    }
    fclose(fbin);
    
}
