#include <stdio.h>
#include <stdlib.h>

class Signal {
  public:
    const char *name;
    int action;
};

const int MEMORY_SIZE = 1000,
           REG_SIZE = 6,

           PROG_EOF  = 0,
           END       = 1,
           EXIT      = 2,
           MOV       = 3,
           CMP       = 4,
           JMP       = 5,
           JE        = 6,
           SET       = 7,
           PRINT     = 8,
           READ      = 9,
           PUSH      = 10,
           POP       = 11,
           AWOKE     = 12,

           SIG_NUM = 4,
           SIGINT  = 0,
           SIGSEGV = 1,
           SIGFPE  = 2,
           SIGUSR  = 3,

           ACTABORT  = 0,
           ACTWARN   = 1,
           ACTIGNORE = 2,
           ACTDUMP   = 3,

           CF        = 1,
           PF        = 4,
           AF        = 16,
           ZF        = 64,
           SF        = 128,
           TF        = 256,
           IF        = 512,
           DF        = 1024,
           OF        = 2048,
           IOPL      = 4096,
           NT        = 8192,

           EAX = 1,
           EBX = 2,
           ECX = 3,
           EDX = 4,
           EIP = 5,
           ESP = 6;

Signal SIG[SIG_NUM] = {{"Interrupted.",                                              ACTABORT},
                       {"Segmentation fault.",                                       ACTDUMP},
                       {"Counting error (division by zero or something like this).", ACTDUMP},
                       {"Signal from user.",                                         ACTWARN}};

char GetReal(int ptr);
void awoke(int signal);

int reg[REG_SIZE + 1] = {};
signed char memory[MEMORY_SIZE] = {};
int eflags = 2 | IF;

int main(int argc, char **argv) {
    FILE *fileptr = NULL;
    int exit = 0;
    int temp = 0, flag_op = 0;

    if (argc < 2) {
        puts("Too few arguments. Use: proc <filepath>");
        return 0;
    }

    if ((fileptr = fopen(argv[1], "r")) < 0) {
        puts("Cannot open input file.");
        return 0;
    }

    printf("Loading code... ");
    for (reg[EIP] = 0; reg[EIP] < MEMORY_SIZE; reg[EIP]++) {
        memory[reg[EIP]] = fgetc(fileptr);
        if (memory[reg[EIP]] == PROG_EOF)
            break;
    }
    if (reg[EIP] >= MEMORY_SIZE) {
        puts("Memory overflow. Aborted.");
        fclose(fileptr);
        return 0;
    }

    puts("Starting...");
    exit = 0;
    reg[ESP] = MEMORY_SIZE - 1;
    for (reg[EIP] = 0; memory[reg[EIP]] != PROG_EOF && !exit; reg[EIP]++) {
        if (reg[EIP] < 0 || reg[EIP] >= MEMORY_SIZE)
            awoke(SIGSEGV);
        switch(memory[reg[EIP]]) {
            case END:
                exit = -1;
                break;
            case EXIT:
                exit = memory[reg[EIP] + 1];
                reg[EIP]++;
                break;
            case MOV:
                if (memory[reg[EIP] + 1] >= 0)
                    memory[memory[reg[EIP] + 1]] = GetReal(memory[reg[EIP] + 2]);
                else
                    reg[-memory[reg[EIP] + 1]] = GetReal(memory[reg[EIP] + 2]);
                reg[EIP] += 2;
                break;
            case CMP:
                if (GetReal(memory[reg[EIP] + 1]) == GetReal(memory[reg[EIP] + 2])) {
                    eflags = eflags | ZF;
                    flag_op = 1;
                }
                reg[EIP] += 2;
                break;
            case JMP:
                reg[EIP] = int(memory[reg[EIP] + 1]) - 1;
                break;
            case JE:
                if (eflags && ZF)
                    reg[EIP] = int(memory[reg[EIP] + 1]) - 1;
                else
                    reg[EIP]++;
                break;
            case SET:
                if (memory[reg[EIP] + 2])
                    eflags = eflags | int(memory[reg[EIP] + 1]);
                else
                    eflags = eflags & !(int(memory[reg[EIP] + 1]));
                flag_op = 1;
                break;
            case PRINT:
                printf("%d\n", GetReal(memory[reg[EIP] + 1]));
                reg[EIP]++;
                break;
            case READ:
                scanf("%d", &temp);
                if (memory[reg[EIP] + 1] >= 0)
                    memory[memory[reg[EIP] + 1]] = char(temp);
                else {
                    if (-memory[reg[EIP] + 1] <= REG_SIZE)
                        reg[-memory[reg[EIP] + 1]] = char(temp);
                    else
                        awoke(SIGSEGV);
                }
                getchar();
                reg[EIP]++;
                break;
            case AWOKE:
                awoke(memory[reg[EIP] + 1]);
                reg[EIP]++;
                break;
            default:
                printf("Unknown comand %d (operator %d). Aborted.\n", memory[reg[EIP]], reg[EIP]);
                exit = -1;
        }

        if (!flag_op) {
            if (eflags && ZF)
                eflags = eflags & !ZF;
        }
        else
            flag_op = 0;
    }

    if (memory[reg[EIP]] == PROG_EOF)
        exit = -1;
    printf("Finished. Exit status: %d", exit);
    if (exit == -1)
        printf(" (aborted)");
    putchar('\n');
    fclose(fileptr);
    return 0;
}

char GetReal(int ptr) {
    if (ptr >= 0)
        return memory[ptr];
    else {
        if (-ptr <= REG_SIZE)
            return (char)reg[-ptr];
        else
            awoke(SIGSEGV);
    }
}

void awoke(int signal) {
    FILE *dump_file = NULL;
    int sig_act = ACTABORT;
    char c = 0;
    if (signal >= SIG_NUM || signal < 0)
        puts("Unknown signal. Aborted.");
    else {
        printf("Received signal %d: %s\n", signal, SIG[signal].name);
        sig_act = SIG[signal].action;
    }

    switch (sig_act) {
        case ACTIGNORE:
            return;
        case ACTWARN:
            puts("Program should be stopped. Do you really want to continue (y / n(recomended))?");
            if ((c = getchar()) == 'y' || c == 'Y') {
                getchar();
                return;
            }
        case ACTDUMP:
            puts("The problem was accured and proccess must be killed. Here is the dump of memory.");
            puts("Send this information and (if it's possible) your source code to developers, and they'll try to solve this problem.");

            puts("Dump of memory.");
            for (int i = 0; i < MEMORY_SIZE && memory[i] != PROG_EOF; i++) {
                if (i % 10 == 0)
                    putchar('\n');
                printf("%6d|", memory[i]);
            }
            puts("\nDump of stack.");
            for (int i = MEMORY_SIZE - 1; i >= reg[ESP]; i--) {
                if (i % 10 == 0)
                    putchar('\n');
                printf("%6d|", memory[i]);
            }
            puts("\nDump of registers.");
            printf("EAX = %d; EBX = %d; ECX = %d; EDX = %d; EIP = %d; ESP = %d.\n", reg[EAX], reg[EBX], reg[ECX], reg[EDX], reg[EIP], reg[ESP]);
            puts("Flags:");
            printf("CF %d; PF %d; AF %d; ZF %d; SF %d; TF %d.\n", bool(eflags & !CF), bool(eflags & !PF), bool(eflags & !AF), bool(eflags & !ZF), bool(eflags & !SF), bool(eflags & !TF));
            printf("IF %d; DF %d; OF %d; IOPL %d; NT %d.", bool(eflags & !IF), bool(eflags & !DF), bool(eflags & !OF), bool(eflags & !IOPL), bool(eflags & !NT));

            if ((dump_file = fopen("dump.txt", "w")) < 0) {
                puts("Cannot create dump file.");
            }
            else {
                fprintf(dump_file, "Dump of memory.\n");
                for (int i = 0; i < MEMORY_SIZE && memory[i] != PROG_EOF; i++) {
                    if (i % 10 == 0)
                        fputc('\n', dump_file);
                    fprintf(dump_file, "%6d|", memory[i]);
                }
                fprintf(dump_file, "\nDump of stack.\n");
                for (int i = MEMORY_SIZE - 1; i >= reg[ESP]; i--) {
                    if (i % 10 == 0)
                        fputc('\n', dump_file);
                    fprintf(dump_file, "%6d|", memory[i]);
                }
                fprintf(dump_file, "\nDump of registers.\n");
                fprintf(dump_file, "EAX = %d; EBX = %d; ECX = %d; EDX = %d; EIP = %d; ESP = %d.\n", reg[EAX], reg[EBX], reg[ECX], reg[EDX], reg[EIP], reg[ESP]);
                fprintf(dump_file, "Flags:\n");
                fprintf(dump_file, "CF %d; PF %d; AF %d; ZF %d; SF %d; TF %d.\n", bool(eflags & !CF), bool(eflags & !PF), bool(eflags & !AF), bool(eflags & !ZF), bool(eflags & !SF), bool(eflags & !TF));
                fprintf(dump_file, "IF %d; DF %d; OF %d; IOPL %d; NT %d.", bool(eflags & !IF), bool(eflags & !DF), bool(eflags & !OF), bool(eflags & !IOPL), bool(eflags & !NT));
                puts("\nDump is automatically saved into file 'dump.txt'.");
                fclose(dump_file);
            }
        case ACTABORT:
            puts("Aborted.");
            exit(1);
    }
}
