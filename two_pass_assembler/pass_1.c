#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct OPTAB {
    char opcode[10];
    int code;
};

int searchOPTAB(char code[], struct OPTAB optab[], int n) {
    for (int i=0 ; i<n ; i++) {
        if (strcmp(code, optab[i].opcode) == 0)
            return 1;
    }

    return 0;
}

int main() {
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;
    char label[20], opcode[20], operand[20], code[20];
    int locctr, start, length;
    
    struct OPTAB optab[50];
    int optabCount = 0;

    //reading optab
    fp2 = fopen("optab.txt", "r");
    if (fp2 == NULL){
        printf("Error : couldnt open file\n");
        exit(0);
    }

    while (fscanf(fp2, "%s %d", optab[optabCount].opcode, &optab[optabCount].code) != EOF) {
        optabCount ++;

    }
    fclose(fp2);

    fp1 = fopen("input.txt", "r");
    fp3 = fopen("intermediate.txt", "w");
    fp4 = fopen("symtab.txt", "w");
    fp5 = fopen("length.txt", "w");

    if (fp1 == NULL) {
        printf("Error: Cannot open input.txt\n");
        exit(0);
    }


    fscanf(fp1, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0){
        start = atoi(operand);
        locctr = start;
        fprintf(fp3, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(fp3, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "**") != 0)
            fprintf(fp4, "%s\t%d\n", label, locctr);

        if (searchOPTAB(opcode, optab, optabCount))
            locctr += 3;
        else if (strcmp(opcode, "WORD") == 0)
            locctr += 3;
        else if (strcmp(opcode, "RESW") == 0)
            locctr += (3 * atoi(operand));
        else if (strcmp(opcode, "RESB") == 0)
            locctr += atoi(operand);
        else if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'X')
                locctr += 1;
            else if (operand[0] == 'C')
                locctr += (strlen(operand) - 3);
        } else
            printf("Invalid opcode: %s\n", opcode);
        
        fscanf(fp1, "%s %s %s", label, opcode, operand);
            
    }

    fprintf(fp3, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    length = locctr - start;
    fprintf(fp5,"Program length =%d\n", length);

    fclose(fp1);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    return 0;
}