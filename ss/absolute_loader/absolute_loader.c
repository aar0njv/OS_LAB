#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMORY_SIZE 10000

char memory[MEMORY_SIZE];

void read_header(FILE *fp, char *progName, int *startAddr, int *length) {
    char recordType;
    fscanf(fp, " %c %s %x %x", &recordType, progName, startAddr, length);
}

int read_text_record(FILE *fp, int *address, char *objectCode) {
    char recordType;
    long pos = ftell(fp);
    if (fscanf(fp, " %c", &recordType) == 1 && recordType == 'T') {
        fscanf(fp, " %x %s", address, objectCode);
        return 1;
    } else {
        fseek(fp, pos, SEEK_SET);
        return 0;
    }
}

void load_code(int address, char *objectCode) {
    int codeLen = strlen(objectCode);
    for (int i = 0; i < codeLen; i += 2) {
        char byteStr[3] = {objectCode[i], objectCode[i+1], '\0'};
        int value;
        sscanf(byteStr, "%2x", &value);
        memory[address++] = (char)value;
    }
}

void read_end_record(FILE *fp, int *entryAddr) {
    char recordType;
    fscanf(fp, " %c %x", &recordType, entryAddr);
}

void display_memory(int startAddr, int length) {
    printf("Loaded Memory: \n");
    for (int i = 0; i < length; i++) {
        printf("%02X ", (unsigned char)memory[startAddr + i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n");
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Error: couldnt open input file\n");
        return 1;
    }

    char progName[20], objectCode[30]; 
    int startAddr, length, address, entryAddr; 

    read_header(fp, progName, &startAddr, &length);

    while (!feof(fp)) {
        if (read_text_record(fp, &address, objectCode)) {
            load_code(address, objectCode);
        } else {
            break;
        }
    }

    read_end_record(fp, &entryAddr);

    display_memory(startAddr, length);

    printf("Entry point: %x\n", entryAddr);

    fclose(fp);
    return 0;
}
