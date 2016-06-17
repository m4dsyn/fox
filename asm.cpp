#include "defines.h"

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

    puts("Assembling code... ");
    fscanf(fileptr, "%s", temp);
    IgnoreRegister(temp);
    for (i = 0; strcmp(temp, name[PROG_EOF]) != 0 && temp[0] != EOF && i < MEMORY_SIZE; i++) {
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
            if (temp[0] != '-')
                AsmNum(fileptr2, atoi(temp));
            else
                fprintf(fileptr2, "%c", atoi(temp));
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
                    if (keyword_name[j] < 0)
                        fprintf(fileptr2, "%c", keyword_name[j]);
                    else
                        AsmNum(fileptr2, keyword_name[j]);
                    break;
                }
            if (j >= KEYWORD_NUM) {
                for (j = 0; j < SIG_NUM; j++)
                    if (strcmp(temp, SIG[j].name) == 0) {
                        AsmNum(fileptr2, j);
                        break;
                    }
                if (j >= SIG_NUM) {
                    for (j = 0; j < INT_NUM; j++)
                        if (INT_LIST[j].name != NULL && strcmp(temp, INT_LIST[j].name) == 0) {
                            AsmNum(fileptr2, j);
                            break;
                        }
                    if (j >= INT_NUM) {
                        printf("Unknon identificator \'%s\'. Ignoring.\n", temp);
                        fprintf(fileptr2, "%s", temp);
                    }
                }
            }
        }
        fscanf(fileptr, "%s", temp);
        IgnoreRegister(temp);
    }
    fprintf(fileptr2, "%c", EOF);
    if (i < MEMORY_SIZE)
        puts("Finished.");
    else
        puts("Too big program. Memory overflow.");

    fclose(fileptr);
    fclose(fileptr2);
    return 0;
}

void IgnoreRegister(char temp[]) {
    for (int i = 0; temp[i] != '\0' && temp[i] != '\n'; i++)
        temp[i] = tolower(temp[i]);
}
