#ifndef FXVM_CORE_HPP
#define FXVM_CORE_HPP

#include <stdint.h>
#include <stack>
#include <stdio.h>
using std::stack;

#define uint uint32_t // !!!!!!!!!!!!!

const int RAM_END = 0xffffffff; //max amount of mem (in bytes)
const int RAM_START = 0xf0000000

enum cmd {
  print, scan,
  mov, cpy, push, pop,
  add, sub, mul, div,
  exit, brk,
  fork, kill,
  alloc, free
}

class core {
  int eax, ebx, ecx, edx; //cannot be printable
  int esx, epx; //for scans and prints
  char *RAM; //allocatible memory
  uint_t memptr; //alloc pointer
  stack <int> local;


public:

  core (): eax (0), //0x0000
           ebx (0), //0x0001
           ecx (0), //0x0002
           edx (0), //0x0003
           esx (0), //0x0004
           epx (0), //0x0005
           RAM (new char [RAM_MAX]), //0x0006 - 0xffffffff
           memptr (0),
           local (stack<int32_t> ())
           {}

  core (const core&);
  ~core () { delete [] reg; delete [] RAM; }

  inline int feed (cmd opc, ...); //run command by opcode | inputs 32bit params
  inline uint16_t //returns amount of allocated memory
    falloc (uint16_t size = 4, char c = 0); //allocate memory in *RAM



}

#undef int

#endif /* end of include guard: FXVM_CORE_HPP */
