#ifndef FX_SIGNAL_HPP
#define FX_SIGNAL_HPP
#include "config.hpp"


int SH_HUP     ();  // signal handler for HUP
int SH_INT     ();  // etc
int SH_QUIT    ();
int SH_ILL     ();
int SH_TRAP    ();
int SH_ABRT    ();
int SH_BUS     ();
int SH_FPE     ();
int SH_KILL    ();
int SH_USR1    ();
int SH_SEGV    ();
int SH_USR2    ();
int SH_PIPE    ();
int SH_ALRM    ();
int SH_TERM    ();

int SH_CHLD    ();
int SH_CONT    ();
int SH_STOP    ();
int SH_STP     ();
int SH_TTIN    ();
int SH_TTOU    ();
int SH_URG     ();
int SH_XCPU    ();
int SH_XFSZ    ();
int SH_VTALRM  ();
int SH_PROF    ();
int SH_WINCH   ();
int SH_IO      ();
int SH_PWR     ();
int SH_SYS     ();

int sh_handler (std::string sig) {
  if (sig == K_USR1) return SH_USR1 ();
}


int SH_HUP     () {
  printf ("signal received.\n");
    return 0;
}

int SH_INT     () {
  printf ("signal received.\n");
  return 0;
}

int SH_QUIT    () {
  printf ("signal received.\n");
  return 0;
}

int SH_ILL     () {
  printf ("signal received.\n");
  return 0;
}

int SH_TRAP    () {
  printf ("signal received.\n");
  return 0;
}

int SH_ABRT    () {
  printf ("signal received.\n");
  return 0;
}

int SH_BUS     () {
  printf ("signal received.\n");
  return 0;
}

int SH_FPE     () {
  printf ("signal received.\n");
  return 0;
}

int SH_KILL    () {
  printf ("signal received.\n");
  return 0;
}

int SH_USR1    () {
  printf ("signal received.\n");
  return 0;
}

int SH_SEGV    () {
  printf ("signal received.\n");
  return 0;
}

int SH_USR2    () {
  printf ("signal received.\n");
  return 0;
}

int SH_PIPE    () {
  printf ("signal received.\n");
  return 0;
}

int SH_ALRM    () {
  printf ("signal received.\n");
  return 0;
}

int SH_TERM    () {
  printf ("signal received.\n");
  return 0;
}

int SH_CHLD    () {
  printf ("signal received.\n");
  return 0;
}

int SH_CONT    () {
  printf ("signal received.\n");
  return 0;
}

int SH_STOP    () {
  printf ("signal received.\n");
  return 0;
}

int SH_STP     () {
  printf ("signal received.\n");
  return 0;
}

int SH_TTIN    () {
  printf ("signal received.\n");
  return 0;
}

int SH_TTOU    () {
  printf ("signal received.\n");
  return 0;
}

int SH_URG     () {
  printf ("signal received.\n");
  return 0;
}

int SH_XCPU    () {
  printf ("signal received.\n");
  return 0;
}

int SH_XFSZ    () {
  printf ("signal received.\n");
  return 0;
}

int SH_VTALRM  () {
  printf ("signal received.\n");
  return 0;
}

int SH_PROF    () {
  printf ("signal received.\n");
  return 0;
}

int SH_WINCH   () {
  printf ("signal received.\n");
  return 0;
}

int SH_IO      () {
  printf ("signal received.\n");
  return 0;
}

int SH_PWR     () {
  printf ("signal received.\n");
  return 0;
}

int SH_SYS     () {
  printf ("signal received.\n");
  return 0;
}







#endif /* end of include guard: FX_SIGNAL_HPP */
