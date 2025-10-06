#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fint, *fop, *fsym, *flen;

    char label[20], opcode[10], operand[20];
    char mnemonic[10], code[10];
    char symtab[20];

    int symaddr, start, len, addr;

    fint = fopen("intermediate.txt", "r");
    fop = fopen("optab.txt", "r");
    fsym = fopen("symtab.txt", "r");
    flen = fopen("length.txt", "r");

    if (!fint || !fop || !fsym || !len) {
        printf("Error opening file(s).");
        return 1;
    }

    fscanf(fint,"%s\t%s\t%s", label, opcode, operand);
    
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
    } else {
        start = 0;
    }

    fscanf(flen, "%d", &len);

    printf("H^%s^%06d^%06X\n", label, start, len);

    while (fscanf(fint, "%d\t%s\t%s\t%s", &addr, label, opcode, operand) == 4) {
        if (strcmp(opcode, "END") == 0)
            break;

        int found = 0;
        rewind(fop);

        while (fscanf(fop,"%s\t%s", mnemonic, code ) == 2) {
            if (strcmp(opcode, mnemonic) == 0) {
                found= 1;
                rewind(fsym);

                int opaddr = 0;
                while (fscanf(fsym,"%s\t%d", symtab, &symaddr) == 2) {
                    if (strcmp(operand, symtab) == 0) {
                        opaddr = symaddr;
                        break;
                    }
                }

                printf("T^%06d^%s%06d\n", addr, code, opaddr);
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                printf("T^%06d^%06X\n", addr, atoi(operand));
            } else if (strcmp(opcode, "BYTE") == 0) {
                printf("T^%06d^%06X\n", addr, atoi(operand));
            }
        }
    }
    
      
        printf("E^%06d\n", start);
    
        fclose(fint);
        fclose(fop);
        fclose(fsym);
        fclose(flen);
    
        return 0;
}
    