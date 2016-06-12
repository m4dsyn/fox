// main
#include <iostream>
#include <stdint.h>
#include <string>

const int REG_SIZE = 32;
const int RAM_MAX = 0xffff;




int main (int argc, char **argv) {
  std::cout << "Not yet! Maybe tomorrow...\n";
  return 0;
}

enum cmd {
  print, scan,
  mov, cpy,
  add, sub, mul, div,

}



class core {
  int64_t eax, ebx, ecx, edx; //cannot be printable
  char *RAM;
  uint8_t memsize;


public:

  core (): eax (0), ebx (0), ecx (0), edx (0), RAM (nullptr), memsize (0) {}
  core (const core&);
  ~core () { delete [] reg; delete [] RAM; }

  inline int feed (char opc, ...);
  inline int falloc (unsigned size = 4, char c = 0);



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
