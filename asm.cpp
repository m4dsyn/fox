#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int COMAND_NUM = 13,
           KEYWORD_NUM = 9,
           MAX_STR_SIZE = 100,

           PROG_EOF = 0,

           SIGINT = 0,
           SIGSEGV = 1,
           SIGFPE  = 2,
           SIGUSR  = 3;

const char *name[COMAND_NUM] = {"eof", "end", "exit", "mov", "cmp", "jmp", "je", "set", "print", "read", "push", "pop", "awoke"};
const char *keyword[KEYWORD_NUM]    = {"eax", "ebx", "ecx", "edx", "eip", "sigint", "sigsegv", "sigfpe", "sigusr"};
const int keyword_name[KEYWORD_NUM] = {-1,    -2,    -3,    -4,    -5,    SIGINT,   SIGSEGV,   SIGFPE,   SIGUSR};

void IgnoreRegister(char temp[]);

int main(int argc, char **argv) {
    FILE *fileptr = NULL;
    FILE *fileptr2 = NULL;
    char temp[MAX_STR_SIZE] = {};
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
        return 0;
    }

    printf("Assembling code... ");
    fscanf(fileptr, "%s", temp);
    IgnoreRegister(temp);
    for (i = 0; strcmp(temp, name[PROG_EOF]) != 0; i++) {
        if (temp[0] == '#' && temp[1] == '#') {
            temp[1] = '-';
            while (1) {
                for (j = 0; temp[j] != '\0'; j++) {
                    if (temp[j] == '#' && temp[j + 1] == '#')
                        break;
                }
                if (temp[j] != '\0')
                    break;
                fscanf(fileptr, "%s", temp);
            }
            fscanf(fileptr, "%s", temp);
            IgnoreRegister(temp);
        }
        if (isdigit(temp[0]) || temp[0] == '-') {
            fprintf(fileptr2, "%c", char(atoi(temp)));
            fscanf(fileptr, "%s", temp);
            IgnoreRegister(temp);
            continue;
        }
        for (j = 1; j < COMAND_NUM; j++)
            if (strcmp(temp, name[j]) == 0) {
                fprintf(fileptr2, "%c", j);
                break;
            }

        if (j >= COMAND_NUM) {
            for (j = 0; j < KEYWORD_NUM; j++)
                if (strcmp(temp, keyword[j]) == 0) {
                    fprintf(fileptr2, "%c", keyword_name[j]);
                    break;
                }
            if (j >= KEYWORD_NUM) {
                printf("Unknon identificator \'%s\'. Ignoring.\n", temp);
                fprintf(fileptr2, "%s", temp);
            }
        }
        fscanf(fileptr, "%s", temp);
        IgnoreRegister(temp);
    }
    fprintf(fileptr2, "%c", 0);
    puts("Finished.");

    fclose(fileptr);
    fclose(fileptr2);
    return 0;
}

void IgnoreRegister(char temp[]) {
    for (int i = 0; temp[i] != '\0' && temp[i] != '\n'; i++)
        temp[i] = tolower(temp[i]);
}
