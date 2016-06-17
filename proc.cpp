#include "defines.h"

int main(int argc, char **argv) {
    FILE *fileptr = NULL;
    int exit = 0, temp = 0;

    if (argc < 2) {
        puts("Too few arguments. Use: proc <filepath>");
        return 0;
    }

    if ((fileptr = fopen(argv[1], "r")) < 0) {
        puts("Cannot open input file.");
        return 0;
    }

    puts("Loading code... ");
    for (reg[EIP] = 0; reg[EIP] < MEMORY_SIZE; reg[EIP]++) {
        memory[reg[EIP]] = fgetc(fileptr);
        if (memory[reg[EIP]] == EOF)
            break;
    }
    if (reg[EIP] >= MEMORY_SIZE) {
        puts("Memory overflow. Aborted.");
        fclose(fileptr);
        return 0;
    }

    puts("Starting...");
    exit = 0;
    reg[ESP] = MEMORY_SIZE;
    reg[EFLAGS] = 2 + IF + TF;
    EIP_STEP = 1;
    for (reg[EIP] = 0; memory[reg[EIP]] != EOF && !exit; reg[EIP] += EIP_STEP) {
        if (ifSet(TF))
            Int(INT_TRACE);
        EIP_STEP = 1;
        if (reg[EIP] < 0 || reg[EIP] >= MEMORY_SIZE)
            awoke(SIGSEGV);
        switch(memory[reg[EIP]]) {
            case END:
                exit = -1;
                break;
            case EXIT:
                exit = GetNum(reg[EIP] + 1);
                break;
            case MOV:
                if (memory[reg[EIP] + 1] >= 0)
                    WriteNum(GetNum(reg[EIP] + 1), GetReal(GetNum(reg[EIP] + EIP_STEP)));
                else {
                    reg[-memory[reg[EIP] + 1]] = GetReal(GetNum(reg[EIP] + 2));
                    reg[EIP]++;
                }
                break;
            case CMP:
                if (GetReal(GetNum(reg[EIP] + 1)) == GetReal(GetNum(reg[EIP] + EIP_STEP)))
                    Switch(ZF, 1);
                break;
            case JMP:
                EIP_STEP = 1;
                reg[EIP] = GetNum(reg[EIP] + 1, 0) - 1;
                break;
            case JE:
                if (ifSet(ZF)) {
                    EIP_STEP = 1;
                    reg[EIP] = GetNum(reg[EIP] + 1, 0) - 1;
                }
                else
                    GetNum(reg[EIP] + 1);
                break;
            case SET: // not tested
                Switch(GetNum(reg[EIP] + 1), GetNum(memory[reg[EIP] + EIP_STEP]));
                break;
            case PRINT:
                printf("%d\n", GetReal(GetNum(reg[EIP] + 1)));
                break;
            case READ:
                puts("Comand 'read' is not longer usable. You should call int 22.");
                Int(INT_KEYBOARD_IN);
                break;
            case PUSH:
                Push(GetReal(GetNum(reg[EIP] + 1)));
                break;
            case POP:
                WriteNum(GetNum(reg[EIP] + 1), Pop());
                break;
            case INT:
                Int(GetNum(reg[EIP] + 1));
                break;
            case AWOKE:
                awoke(GetNum(reg[EIP] + 1));
                break;
            default:
                printf("Unknown comand %d (operator %d). Aborted.\n", memory[reg[EIP]], reg[EIP]);
                awoke(SIGSEGV);
                exit = -1;
        }
    }

    if (memory[reg[EIP]] == EOF)
        exit = -1;
    printf("Finished. Exit status: %d", exit);
    if (exit == -1)
        printf(" (aborted)");
    putchar('\n');
    fclose(fileptr);
    return 0;
}
