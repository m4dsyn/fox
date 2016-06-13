#ifndef FXVM_CORE_CPP
#define FXVM_CORE_CPP





#include "core.hpp"
#define int int16_t

core :: core (const core& src) {
  eax = src.eax;
  ebx = src.ebx;
  ecx = src.ecx;
  edx = src.edx;
  memsize = src.memsize;
  for (int i = 0; i < src.memsize; i++)
    RAM [i] = src.RAM [i];

}

uint16_t core :: falloc (uint16_t size = 4, char c = 0) {
  if (memptr + size >= RAM_MAX) return 0;

  memptr += size;
  return size;

}



#undef int

#endif /* end of include guard: FXVM_CORE_CPP */
