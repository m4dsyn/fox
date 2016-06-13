#ifndef FXVM_CORE_HPP
#define FXVM_CORE_HPP

#include <stdint.h>
#include <stack>
using std::stack;

#define int int16_t // !!!!!!!!!!!!!

const int RAM_MAX = 0xffff; //max amount of mem (in bytes)

enum cmd {
  print, scan,
  mov, cpy, push, pop,
  add, sub, mul, div,
  exit, brk,
  fork, kill,
  alloc, free
}

class core {
  int32_t eax, ebx, ecx, edx; //cannot be printable
  char *RAM; //allocatible memory
  uint8_t memptr; //alloc pointer
  stack <int32_t> local;

public:

  core (): eax (0),
           ebx (0),
           ecx (0),
           edx (0),
           RAM (new char [RAM_MAX]),
           memptr (0),
           local (stack ())
           {}

  core (const core&);
  ~core () { delete [] reg; delete [] RAM; }

  inline int feed (char opc, ...); //run command by opcode | inputs 32bit params
  inline uint16_t //returns amount of allocated memory
    falloc (uint16_t size = 4, char c = 0); //allocate memory in *RAM



}

#undef int

#endif /* end of include guard: FXVM_CORE_HPP */
