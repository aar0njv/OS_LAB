#include <stdio.h>
int main() {
    FILE *in, *out;
    char label;
    int start_addr, orig_start, prog_len;
    int rec_start, no_pairs, opcode, operand, reloc;

    printf("Enter new starting address: ");
    scanf("%d", &start_addr);

    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");

    fscanf(in, " %c", &label);
    if (label == 'H') {
        fscanf(in, "%d %d", &orig_start, &prog_len);
        reloc = start_addr - orig_start;
    }

    while (fscanf(in, " %c", &label) && label != 'E') {
        if (label == 'T') {
            fscanf(in, "%d %d", &rec_start, &no_pairs);
            rec_start += reloc;
            for (int i = 0; i < no_pairs; i++) {
                fscanf(in, "%d %d", &opcode, &operand);
                operand += reloc; // always relocate
                fprintf(out, "%d\t%d\t%d\n", rec_start, opcode, operand);
                rec_start += 3; // assuming 3-byte instructions
            }
        }
    }
    fclose(in);
    fclose(out);
    printf("Relocation complete.\n");
    return 0;
}
