// main
#include <iostream>
#include <stdint.h>
#include <string>

const int RAM_MAX = 0xffff; //max amount of mem (in bytes)


int32_t fscan (); //scan a hex number e.g. 0xff


int main (int argc, char **argv) { //just main
  if (argc < 2) {
    std::cout << "fxvm: fatal error: no input files\nrunning terminated.\n";
    return 1;
  }

  if (argv [1] == "--help") {
    std::cout << "fxvm is fox lang low-level virtual machine.\n";
    std::cout << "Usage: fxvm [options] file\n";
    std::cout << "Options:\n";
    std::cout << "  -m <n> multicore mode with n cores\n";
  }

  for (int i = 1; i < argc; i++) {
    if (argv [i] == -m) {
      i++;

    }
  }

  return 0;
}

enum cmd {
  print, scan,
  mov, cpy, push, pop,
  add, sub, mul, div,

}



class core {
  int32_t eax, ebx, ecx, edx; //cannot be printable
  char *RAM; //allocatible memory
  uint8_t memptr; //alloc pointer


public:

  core (): eax (0), ebx (0), ecx (0), edx (0), RAM (nullptr), memptr (0) {}
  core (const core&);
  ~core () { delete [] reg; delete [] RAM; }

  inline int feed (char opc, ...); //run command by opcode
  inline int falloc (uint16_t size = 4, char c = 0); //allocate memory in *RAM



}

core :: core (const core& src) {
  eax = src.eax;
  ebx = src.ebx;
  ecx = src.ecx;
  edx = src.edx;
  memsize = src.memsize;
  for (int i = 0; i < src.memsize; i++)
    RAM [i] = src.RAM [i];

}

inline int core :: falloc (uint16_t size = 4, char c = 0) {

}
