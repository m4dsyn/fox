const int REG_SIZE = 7,

           EAX    = 2,
           EBX    = 3,
           ECX    = 4,
           EDX    = 5,
           EIP    = 6,
           ESP    = 7,
           EFLAGS = 8,

           CF        = 1,    // overlow flag
           PF        = 4,
           AF        = 16,   // aditional overlow flag
           ZF        = 64,   // zero flag
           SF        = 128,  // sign flag
           TF        = 256,  // trace flag
           IF        = 512,  // interrupt flag
           DF        = 1024,
           OF        = 2048,
           IOPL      = 4096,
           NT        = 8192;

int reg[REG_SIZE + 2] = {};

bool ifSet(int flag);
bool Switch(int flag, bool position);

bool ifSet(int flag) {
    if (reg[EFLAGS] / flag - (reg[EFLAGS] / (2 * flag) * 2))
        return 1;
    return 0;
}

bool Switch(int flag, bool position) {
    if (position && !ifSet(flag))
        reg[EFLAGS] += flag;
    else if (!position && ifSet(flag))
        reg[EFLAGS] -= flag;
}
