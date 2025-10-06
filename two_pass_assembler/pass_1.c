#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void passOne(char label[10], char opcode[10], char operand[10], char code[10], char mnemonic[3]) {
    int locctr, start, length;  // initialize start, locctr, length
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("intermediate.txt", "w");
    fp5 = fopen("length.txt", "w");

    fscanf(fp1,"%s\t%s\t%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fp4, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1,"%s\t%s\t%s", label, opcode, operand);
    }

    else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {

        fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);    //write to int file

        if (strcmp(label,"**") != 0) {      //if label not empty
            fprintf(fp3,"%s\t%d\n", label, locctr);
        }

        fscanf(fp2, "%s\t%s", code, mnemonic);  //read optab

        while (strcmp(code, "END") != 0) {
            if (strcmp(opcode, code) == 0) {    //if already in optab
                locctr += 3;
                break;
            }
            //not in optab, do nothing, skip
            fscanf(fp2,"%s\t%s", code, mnemonic);
        }

        if (strcmp(opcode, "WORD") == 0)
            locctr += 3;
        else if (strcmp(opcode, "RESW") == 0)
            locctr += 3*(atoi(operand));
        else if (strcmp(opcode, "RESB") == 0)
            locctr += atoi(operand);
        else if (strcmp(opcode, "BYTE") == 0)
            ++locctr;

        fscanf(fp1,"%s\t%s\t%s", label, opcode, operand);

    }

    fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    fclose(fp4);
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);

    length = locctr - start;
    fprintf(fp5, "%d", length);
    fclose(fp5);

    printf("\n Length of the code : %d \n", length);

}


int main() {
    char label[10], opcode[10], operand[10];
    char code[10], mnemonic[3];
    passOne(label, opcode, operand, code, mnemonic);
    return 0;
}