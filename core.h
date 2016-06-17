class Interruption {
  public:
    const char *name;
    const char *message;
    bool if_show_message;
    void *handler(int int_num);
};

const int INT_NUM         = 35,
           INT_DIVZERO     = 0,
           INT_TRACE       = 1,
           INT_OWERFLOW    = 4,
           INT_PRINTSCREEN = 5,
           INT_RESERVE1    = 6,
           INT_RESERVE2    = 7,
           INT_KEYBOARD_IN = 22,
           INT_FINISH      = 32;
void Int_handle(int int_num);
Interruption INT_LIST[INT_NUM] = {{"int_divzero", "Division by zero.", 1, &Int_handle},    {"int_trace", "Trace flag set.", 0, &Int_handle}, {NULL, NULL, 0, NULL},                                      {NULL, NULL, 0, NULL}, {"int_overflow", "Overflow.", 1, &Int_handle},
                                  {"int_printscreen", "Printing screen.", 0, &Int_handle}, {"int_reserve1", "Ignoring.", 0, NULL},          {"int_reserve2", "Ignoring.", 0, NULL},                     {NULL, NULL, 0, NULL}, {NULL, NULL, 0, NULL},
                                  {NULL, NULL, 0, NULL},                                  {NULL, NULL, 0, NULL},                           {NULL, NULL, 0, NULL},                                      {NULL, NULL, 0, NULL}, {NULL, NULL, 0, NULL},
                                  {NULL, NULL, 0, NULL},                                  {NULL, NULL, 0, NULL},                           {NULL, NULL, 0, NULL},                                      {NULL, NULL, 0, NULL}, {NULL, NULL, 0, NULL},
                                  {NULL, NULL, 0, NULL},                                  {NULL, NULL, 0, NULL},                           {"int_keyboard_in", "Input form keyboard.", 0, &Int_handle}, {NULL, NULL, 0, NULL}, {NULL, NULL, 0, NULL},
                                  {NULL, NULL, 0, NULL},                                  {NULL, NULL, 0, NULL},                           {NULL, NULL, 0, NULL},                                      {NULL, NULL, 0, NULL}, {NULL, NULL, 0, NULL},
                                  {NULL, NULL, 0, NULL},                                  {NULL, NULL, 0, NULL},                           {"int_finish", "Program stopped.", 1, &Int_handle}};

void Push(int num);
int  Pop(void);
void Int(int int_num);

void Push(int num) {
    int i = 0, temp = num;
    for (i = 0; temp > 0; i++)
        temp /= 256;
    reg[ESP] -= (i + 1);
    memory[reg[ESP]] = i;
    for (; i > 0; i--) {
        memory[reg[ESP] + i] = num % 256;
        num /= 256;
    }
}

int Pop(void) {
    int temp = 0;
    if (reg[ESP] >= MEMORY_SIZE || reg[ESP] < 0) {
        Int(INT_OWERFLOW);
        return 0;
    }
    temp = GetNum(reg[ESP], 0);
    reg[ESP] += memory[reg[ESP]] + 1;
    return temp;
}

void Int(int int_num) {
    if (INT_LIST[int_num].name == NULL) {
        printf("Unknown interruption %d. Ignored.", int_num);
        awoke(SIGWARN);
        return;
    }
    if (INT_LIST[int_num].if_show_message)
        printf("Interruption %s (%d): %s", INT_LIST[int_num].name, int_num, INT_LIST[int_num].message);
    (*(INT_LIST[int_num].handler))(int_num);
}

void Int_handle(int int_num) {
    int temp = 0;
    switch(int_num) {
        case INT_DIVZERO:
            awoke(SIGFPE);
            break;
        case INT_TRACE:
            Dump(stdout);
            getchar();
            break;
        case INT_OWERFLOW:
            awoke(SIGSEGV);
            break;
        case INT_PRINTSCREEN:
            puts("Cannot print screen");
            break;
        case INT_RESERVE1:
        case INT_RESERVE2:
            break;
        case INT_KEYBOARD_IN:
            scanf("%d", &temp);
            WriteNum(GetNum(reg[EIP] + 1), temp);
            getchar();
            break;
        case INT_FINISH:
            exit(0);
            break;
        default:
            printf("Unknown interruption %d. Ignored.", int_num);
            awoke(SIGWARN);
    }
}
