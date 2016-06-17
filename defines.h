// includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// headers
#include "registers.h"
#include "memory.h"

// for prog.cpp

const int PROG_EOF  = 0,
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
           INT       = 12,
           AWOKE     = 13;

int EIP_STEP = 1;

// core
#include "signal.h"

// for asm.cpp
const int COMAND_NUM = 14,
           KEYWORD_NUM = 17,
           MAX_STR_SIZE = 100;

const char *name[COMAND_NUM] = {"eof", "end", "exit", "mov", "cmp", "jmp", "je", "set", "print", "read", "push", "pop", "int", "awoke"};
const char *keyword[KEYWORD_NUM]    = {"eax", "ebx", "ecx", "edx", "eip", "eflags", "cf", "pf", "af", "zf", "sf", "tf", "if", "df", "of", "iopl", "nt"};
const int keyword_name[KEYWORD_NUM] = {-EAX,  -EBX,  -ECX,  -EDX,  -EIP,  -EFLAGS,   CF,   PF,   AF,   ZF,   SF,   TF,   IF,   DF,   OF,   IOPL,   NT};


#include "number.h"
#include "core.h"

