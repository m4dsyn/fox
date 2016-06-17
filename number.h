int GetReal(int ptr);
int GetNum(int ptr, bool if_eip_change);
void WriteNum(int ptr, int num);
void AsmNum(FILE *fileptr, int num);
void DisAsmNum(FILE *fileptr, int num);

int GetReal(int ptr) {
    if (ptr >= 0)
        return GetNum(ptr, 0);
    else {
        if (-ptr <= REG_SIZE) {
            EIP_STEP++;
            return reg[-ptr];
        }
        else
            awoke(SIGSEGV);
    }
}

int GetNum(int ptr, bool if_eip_change = 1) {
    int i = 0, res = 0;

    if (ptr < 0 || memory[ptr] <= 0 || memory[ptr] + ptr >= MEMORY_SIZE) {
        if (memory[ptr] <= 0)
            return memory[ptr];
        puts("In 'GetNum()':");
        awoke(SIGSEGV);
    }

    for (i = 1; i <= memory[ptr]; i++) {
        res *= 256;
        res += memory[ptr + i];
    }
    if (if_eip_change)
        EIP_STEP += memory[ptr] + 1;
    return res;
}

void WriteNum(int ptr, int num) {
    int i = 0, temp = 0;

    if (ptr < 0) {
        if (-ptr <= REG_SIZE) {
            reg[-ptr] = num;
            return;
        }
        else
            awoke(SIGSEGV);
    }

    temp = num;
    for (i = 0; temp > 0; i++)
        temp /= 256;
    if (i > memory[ptr]) {
        Switch(CF, 1);
        i = memory[ptr];
    }
    for (; i > 0; i--) {
        memory[ptr + i] = num % 256;
        num /= 256;
    }
}

void AsmNum(FILE *fileptr, int num) {
    int i = 0, temp = 0;
    temp = num;
    for (i = 0; temp > 0; i++)
        temp /= 256;
    fprintf(fileptr, "%c", i);
    for (; i > 0; i--) {
        fprintf(fileptr, "%c", num % 256);
        num /= 256;
    }
}

void DisAsmNum(FILE *fileptr, int num) {
    int i = 0;
    if (num >= 0)
        fprintf(fileptr, "%d ", num);
    else {
        for (i = 0; i < KEYWORD_NUM; i++)
            if (num == keyword_name[i]) {
                fprintf(fileptr, "%s ", keyword[i]);
                break;
            }
    }
}
