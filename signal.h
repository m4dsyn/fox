class Signal {
  public:
    const char *name;
    const char *message;
    int action;
};

const int SIG_NUM = 39,
           SIGHUP    = 0,
           SIGINT    = 1,
           SIGQUIT   = 2,
           SIGILL    = 3,
           SIGABRT   = 4,
           SIGFPE    = 5,
           SIGKILL   = 6,
           SIGSEGV   = 7,
           SIGPIPE   = 8,
           SIGALRM   = 9,
           SIGTERM   = 10,
           SIGUSR1   = 11,
           SIGUSR2   = 12,
           SIGCHLD   = 13,
           SIGCONT   = 14,
           SIGSTOP   = 15,
           SIGTSTP   = 16,
           SIGTTIN   = 17,
           SIGTTOU   = 18,
           SIGBUS    = 19,
           SIGPOLL   = 20,
           SIGPROF   = 21,
           SIGSYS    = 22,
           SIGTRAP   = 23,
           SIGURG    = 24,
           SIGVTALRM = 25,
           SIGXCPU   = 26,
           SIGXFSZ   = 27,
           SIGIOT    = 28,
           SIGEMT    = 29,
           SIGSTKFLT = 30,
           SIGIO     = 31,
           SIGCLD    = 32,
           SIGPWR    = 33,
           SIGINFO   = 34,
           SIGLOST   = 35,
           SIGWINCH  = 36,
           SIGUNUSED = 37,
           SIGWARN   = 38,

           ACTABORT  = 0,
           ACTWARN   = 1,
           ACTIGNORE = 2,
           ACTDUMP   = 3;

Signal SIG[SIG_NUM] = {{"sighup"   , "Terminal doesn't work.",                                    ACTABORT},
                       {"sigint"   , "Interrupted.",                                              ACTABORT},
                       {"sigquit"  , "Finished.",                                                 ACTDUMP},
                       {"sigill"   , "Illegal instruction.",                                       ACTDUMP},
                       {"sigabrt"  , "Aborted.",                                                  ACTDUMP},
                       {"sigfpe"   , "Counting error (division by zero or something like this).", ACTDUMP},
                       {"sigkill"  , "Killed.",                                                   ACTABORT},
                       {"sigsegv"  , "Segmentation fault.",                                       ACTDUMP},
                       {"sigpipe"  , "Pipe error.",                                               ACTABORT},
                       {"sigalrm"  , "Signal from alarm.",                                        ACTABORT},
                       {"sigterm"  , "Finished.",                                                 ACTABORT},
                       {"sigusr1"  , "Signal from user.",                                         ACTABORT},
                       {"sigusr2"  , "Signal from user.",                                         ACTABORT},
                       {"sigchld"  , "Child process stopped.",                                    ACTIGNORE},
                       {"sigcont"  , "Continue.",                                                 ACTIGNORE},
                       {"sigstop"  , "Stop.",                                                     ACTIGNORE},
                       {"sigtstp"  , "Stop from terminal.",                                       ACTIGNORE},
                       {"sigttin"  , "Terminal's input for resident.",                            ACTIGNORE},
                       {"sigttou"  , "Terminal's output for resident.",                           ACTIGNORE},
                       {"sigbus"   , "Bus error.",                                                ACTDUMP},
                       {"sigpoll"  , "Asking for an action.",                                     ACTABORT},
                       {"sigprof"  , "Profilling timer.",                                         ACTABORT},
                       {"sigsys"   , "Wrong argument or system call.",                            ACTDUMP},
                       {"sigtrap"  , "Signal from trap.",                                         ACTDUMP},
                       {"sigurg"   , "Socket's important message.",                               ACTIGNORE},
                       {"sigvtalrm", "Virtual timer's signal.",                                   ACTABORT},
                       {"sigxcpu"  , "CPU time limit.",                                           ACTDUMP},
                       {"sigxfsz"  , "Too large file.",                                           ACTDUMP},
                       {"sigiot"   , "Aborted.",                                                  ACTDUMP},
                       {"sigemt"   , "Signal from emulator trap.",                                ACTDUMP},
                       {"sigstkflt", "CPU stack error (unused).",                                 ACTABORT},
                       {"sigio"    , "I/O is aviable now.",                                       ACTABORT},
                       {"sigcld"   , "Child process stopped.",                                    ACTIGNORE},
                       {"sigpwr"   , "Power off.",                                                ACTABORT},
                       {"siginfo"  , "Power off.",                                                ACTABORT},
                       {"siglost"  , "File lock lost.",                                           ACTABORT},
                       {"sigwinch" , "Window size changed.",                                      ACTIGNORE},
                       {"sigunused", "Unused signal.",                                            ACTABORT},
                       {"sigwarn"  , "Warning.",                                                  ACTWARN}};

void awoke(int signal);
void Dump(FILE *dump_file);

void awoke(int signal) {
    FILE *dump_file = NULL;
    int sig_act = ACTABORT;
    char c = 0;
    if (signal >= SIG_NUM || signal < 0)
        puts("Unknown signal. Aborted.");
    else {
        sig_act = SIG[signal].action;
        if (sig_act == ACTIGNORE)
            return;
        printf("Received signal %s (%d): %s\n", SIG[signal].name, signal, SIG[signal].message);
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

            Dump(stdout);

            if ((dump_file = fopen("dump.txt", "w")) < 0) {
                puts("Cannot create dump file.");
            }
            else {
                Dump(dump_file);
                puts("\nDump is automatically saved into file 'dump.txt'.");
                fclose(dump_file);
            }
        case ACTABORT:
            puts("Aborted.");
            exit(1);
    }
}

void Dump(FILE *dump_file) {
    int i = 0;
    fprintf(dump_file, "Dump of memory.");
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
    fprintf(dump_file, "CF %1d; PF %1d; AF %1d; ZF   %1d; SF %1d; TF %1d.\n", ifSet(CF), ifSet(PF), ifSet(AF), ifSet(ZF),   ifSet(SF), ifSet(TF));
    fprintf(dump_file, "IF %1d; DF %1d; OF %1d; IOPL %1d; NT %1d.",           ifSet(IF), ifSet(DF), ifSet(OF), ifSet(IOPL), ifSet(NT));
}
