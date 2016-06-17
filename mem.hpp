#ifndef FX_MEM_HPP
#define FX_MEM_HPP

#include <string>
#include "config.hpp"
#include "tools.hpp"




class mem {
  int32_t eax,
          ebx,
          ecx,
          edx,
          esp;
  size_t memsize;
  char *p_mem;

public:

  mem (): eax (0), ebx (0), ecx (0), edx (0), esp (0),
          p_mem (new char [16384])
          {}
  mem (const mem&); // veeeeery slow just try not to use it
  mem (size_t size): eax (0), ebx (0), ecx (0), edx (0), esp (0),
                     memsize (size), p_mem (new char [memsize])
                     {}
  ~mem () { delete [] p_mem; }

  void    set (std::string addr, int32_t val);
  int32_t get (std::string addr); // addr may be address or register e.g. "eax"
  //void put (int32_t val, std::string addr);

  void reset (); // clears all
  void realloc (size_t delta); // veeeeery slow - adds delta bytes to memory



};

mem :: mem (const mem& src) {
  eax = src.eax;
  ebx = src.ebx;
  ecx = src.ecx;
  edx = src.edx;
  esp = src.esp;

  memsize = src.memsize;

  for (size_t i = 0; i < memsize; i++)
    p_mem [i] = src.p_mem [i];
}

int32_t mem :: get (std::string addr) {
  if      (addr == K_EAX) return eax;
  else if (addr == K_EBX) return ebx;
  else if (addr == K_ECX) return ecx;
  else if (addr == K_EDX) return edx;
  else if (addr == K_ESP) return esp;

  else if (ishexstr (addr)) {
    return p_mem [strtoint (addr)];
  }

  //else return NULL;

}

void mem :: set (std::string addr, int32_t val) {
  if      (addr == K_EAX) eax = val;
  else if (addr == K_EBX) ebx = val;
  else if (addr == K_ECX) ecx = val;
  else if (addr == K_EDX) edx = val;
  else if (addr == K_ESP) esp = val;

  else if (ishexstr (addr)) {
    p_mem [strtoint (addr)] = val;
  }

  //else return NULL;

}

void mem :: reset () {
  eax = ebx = ecx = edx = esp = 0;
  delete [] p_mem;
  p_mem = new char [memsize];
}

void mem :: realloc (size_t delta) {
  if (memsize + delta < memsize)
    return; // checks if size_t is enough for memsize + delta

  char* tmp = new char [memsize];
  for (size_t i = 0; i < memsize; i++)
    tmp [i] = p_mem [i];

  delete [] p_mem;
  p_mem = new char [memsize + delta];
  for (size_t i = 0; i < memsize; i++)
    p_mem [i] = tmp [i];

  delete [] tmp;
  memsize += delta;

}

#endif /* end of include guard: FX_MEM_HPP */
