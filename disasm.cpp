#include "defines.h"

int main(int argc, char **argv) {
    FILE *fileptr = NULL;
    FILE *fileptr2 = NULL;
    char temp_str[MAX_STR_SIZE] = "";
    int i = 0, j = 0;

    if (argc < 3) {
        puts("Too few arguments. Use: asm <input filepath> <output filepath>");
        return 0;
    }

    if ((fileptr = fopen(argv[1], "r")) < 0) {
        puts("Cannot open input file.");
        return 0;
    }
    if ((fileptr2 = fopen(argv[2], "w")) < 0) {
        puts("Cannot open output file.");
        fclose(fileptr);
        return 0;
    }

    int exit = 0;

    puts("Loading code... ");
    for (reg[EIP] = 0; reg[EIP] < MEMORY_SIZE; reg[EIP]++) {
        memory[reg[EIP]] = fgetc(fileptr);
        if (memory[reg[EIP]] == EOF)
            break;
    }
    if (reg[EIP] >= MEMORY_SIZE) {
        puts("Memory overflow. Aborted.");
        fclose(fileptr);
        fclose(fileptr2);
        return 0;
    }

    puts("Disassembling code... ");
    fprintf(fileptr2, "## Created by disasm ##");
    reg[ESP] = MEMORY_SIZE;
    for (reg[EIP] = 0; memory[reg[EIP]] != EOF; reg[EIP] += EIP_STEP) {
        EIP_STEP = 1;
        if (reg[EIP] < 0 || reg[EIP] >= MEMORY_SIZE)
            awoke(SIGSEGV);
        switch(memory[reg[EIP]]) {
            case END:
                fprintf(fileptr2, "\n%s ", name[memory[reg[EIP]]]);
                break;
            case EXIT:
            case JMP:
            case JE:
            case SET:
            case PRINT:
            case READ:
            case AWOKE:
                fprintf(fileptr2, "\n%s ", name[memory[reg[EIP]]]);
                DisAsmNum(fileptr2, GetNum(reg[EIP] + 1));
                if (GetNum(reg[EIP] + 1, 0) < -1)
                    EIP_STEP++;
                break;
            case MOV:
            case CMP:
                fprintf(fileptr2, "\n%s ", name[memory[reg[EIP]]]);
                if (memory[reg[EIP] + 1] < 0) {
                    DisAsmNum(fileptr2, GetNum(reg[EIP] + 1, 0));
                    DisAsmNum(fileptr2, GetNum(reg[EIP] + 2));
                    reg[EIP]++;
                }
                else {
                    DisAsmNum(fileptr2, GetNum(reg[EIP] + 1));
                    DisAsmNum(fileptr2, GetNum(reg[EIP] + EIP_STEP));
                }
                break;
            default:
                printf("\nUnknown comand %d (operator %d). Ignored.", memory[reg[EIP]], reg[EIP]);
                fprintf(fileptr2, "%c", memory[reg[EIP]]);
        }
    }
    fprintf(fileptr2, "%s", name[PROG_EOF]);

    puts("\nFinished.");
    putchar('\n');
    fclose(fileptr);
    fclose(fileptr2);
    return 0;
}
