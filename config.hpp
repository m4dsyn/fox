#ifndef FX_CONFIG_HPP
#define FX_CONFIG_HPP

// --------------keywords-----------
std::string      KW_EOF = "eof", // alone
                 KW_MOV = "mov", // address and/or reg only
                 KW_CMP = "cmp", // address and/or reg only
                 KW_JMP = "jmp", // label only
                 KW_JEZ = "jez", // after cmp only & address only
                 KW_JNZ = "jnz", // after cmp only & address only
                 KW_JLZ = "jlz", // after cmp only & address only
                 KW_JGZ = "jgz", // after cmp only & address only
                 KW_SET = "set", // reg and number only
                 KW_PNT = "pnt", // reg or address only
                 KW_PSH = "psh", // reg or address only
                 KW_POP = "pop", // reg or address only
                 KW_SCN = "scn", // reg or address only
                 KW_SIG = "sig", // S_<signal> only
                 KW_INT = "int", // number only

                 K_HUP     = "HUP",
                 K_INT     = "INT",
                 K_QUIT    = "QUIT",
                 K_ILL     = "ILL",
                 K_TRAP    = "TRAP",
                 K_ABRT    = "ABRT",
                 K_BUS     = "BUS",
                 K_FPE     = "FPE",
                 K_KILL    = "KILL",
                 K_USR1    = "USR1",
                 K_SEGV    = "SEGV",
                 K_USR2    = "USR2",
                 K_PIPE    = "PIPE",
                 K_ALRM    = "ALRM",
                 K_TERM    = "TERM",

                 K_CHLD    = "CHLD",
                 K_CONT    = "CONT",
                 K_STOP    = "STOP",
                 K_STP     = "STP",
                 K_TTIN    = "TTIN",
                 K_TTOU    = "TTOU",
                 K_URG     = "URG",
                 K_XCPU    = "XCPU",
                 K_XFSZ    = "XFSZ",
                 K_VTALRM  = "VTALRM",
                 K_PROF    = "PROF",
                 K_WINCH   = "WINCH",
                 K_IO      = "IO",
                 K_PWR     = "PWR",
                 K_SYS     = "SYS",



                 K_EAX = "eax",
                 K_EBX = "ebx",
                 K_ECX = "ecx",
                 K_EDX = "edx",
                 K_ESP = "esp";

// --------------opcodes-------------

static const int _eof = 0,
                 _mov = 1,
                 _cmp = 2,
                 _jmp = 3,  // jump
                 _jeq = 4,  // jump if equal (use after cmp only)
                 _jez = 5,  // equal zero
                 _jnz = 6,  // not sero
                 _jlz = 7,  // less zero
                 _jgz = 8,  // grander zero
                 _set = 9,
                 _pnt = 10,  // print
                 _psh = 11, // push
                 _pop = 12,
                 _scn = 13, // scan
                 _sig = 14, // signal
                 _int = 15, // interrupt

// --------------signals-------------
                 S_HUP    = 1,
                 S_INT    = 2,
                 S_QUIT   = 3,
                 S_ILL     = 4,
                 S_TRAP    = 5,
                 S_ABRT    = 6,
                 S_BUS     = 7,
                 S_FPE     = 8,
                 S_KILL    = 9,
                 S_USR1    = 10,
                 S_SEGV    = 11,
                 S_USR2    = 12,
                 S_PIPE    = 13,
                 S_ALRM    = 14,
                 S_TERM    = 15,

                 S_CHLD    = 17,
                 S_CONT    = 18,
                 S_STOP    = 19,
                 S_STP     = 20,
                 S_TTIN    = 21,
                 S_TTOU    = 22,
                 S_URG     = 23,
                 S_XCPU    = 24,
                 S_XFSZ    = 25,
                 S_VTALRM  = 26,
                 S_PROF    = 27,
                 S_WINCH   = 28,
                 S_IO      = 29,
                 S_PWR     = 30,
                 S_SYS     = 31,

// --------------registers------------


                 eax = 0,
                 ebx = 1,
                 ecx = 2,
                 edx = 3,
                 esp = 4,

                 reg_num = 5;

const int zero_reg [reg_num] = {0, 0, 0, 0, 0};
// because cannot assign {} to array in mem.hpp

















#endif /* end of include guard: FX_CONFIG_HPP */
