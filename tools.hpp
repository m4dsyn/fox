#ifndef FX_TOOLS_HPP
#define FX_TOOLS_HPP




#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
using std::string;

#include "signal.hpp"

int std_fscanf (FILE* file, string fmt, string& str); //fscanf for std::string

bool ishexstr (string str); // checks if string suits 0x<somne_hex>

int32_t strtoint (string str); // converts hex str to int e.g. "0x32" -> 50


#include "mem.hpp" // kostyl


int32_t strtoint (string str) {
  return strtoul (str.c_str () + 2, NULL, 16);
  //                          ^^^^ ignores 0x at the start
}

bool ishexstr (string str) {
  if (str [0] == '0' && str [1] == 'x') {
    for (int i = 2; i < str.size (); i++) {
      if (!isxdigit (str [i]))
        return false;
    }
    return true;
  }
  return false;
}





int std_fscanf (FILE* file, string fmt, string& str)  {
  const char* cstr = str.c_str ();
  const char* cfmt = fmt.c_str ();

  int res = fscanf (file, cfmt, cstr);

  str = cstr;
  return res;

}



#endif /* end of include guard: FX_TOOLS_HPP */
