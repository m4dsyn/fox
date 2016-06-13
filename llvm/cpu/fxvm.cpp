// main
#include <iostream>
#include <stdint.h>
#include <string>
#include <unistd.h>
#include "core.cpp"

int32_t fscan (); //scan a hex number e.g. 0xff


int main (int argc, char **argv) { //just main
  if (argc < 2) {
    std::cout << "fxvm: fatal error: no input files\nexec terminated.\n";
    return 1;
  }

  FILE *code;

  while (int opt = getopt (argc, argv, "h") != -1) {
    switch (opt) {
      case 'h': {
        std::cout << "fxvm is fox lang low-level virtual machine.\n";
        std::cout << "Usage: fxvm -i file [options] \n";
        std::cout << "Options:\n";
        std::cout << "  -h  -- this help\n";
        std::cout << "  -i  -- input file\n";
        break;
      }

      case 'i': {
        if (!(code = fopen (optarg))) {
          std::cout << "fxvm: fatal error: error while opening file\n";
          std::cout << "exec terminated.\n";
          return 1;
        }

      }


      case '?': {
        std::cout << "fxvm: fatal error: no argumants for " << optopt;
        std::cout << "\nexec terminated.\n";
        return 1;
      }
    }

    core

  }


  for (int i = 1; i < argc; i++) {
    if (argv [i] == -m) {
      i++;

    }
  }

  return 0;
}
