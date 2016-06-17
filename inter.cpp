#include "tools.hpp"
#include "config.hpp"
#include "mem.hpp"

#define errret(MSG) return (1 | printf (MSG)) // always true

int main (int argc, char **argv) {
  //printf ("OK");
  if (argc < 2) {
    printf ("Usage: asm <file_in> <file_out>.\n");
    //return 1;
  }

  FILE *f_in;

  mem RAM (16384); // registers and 16KiB of dynamic memory

  int val;     // for integer vars e.g. scn
  string cmd,  // next command
         name, // next variable's name
         to,   // for mov and so on
         from, // ^^^^^^^^^^^^^^^^^
         hex;  // integer input e.g. 0x<some_hex>
  if (!(f_in = fopen ("source.txt", "r"))) {
    printf ("input file error.\n");
    return 2;
  }



  std_fscanf (f_in, "%s", cmd);
  for (size_t i = 0; cmd != KW_EOF || cmd[0] != EOF; i++) {
    if (cmd == KW_MOV) {
      std_fscanf (f_in, "%s", to);
      std_fscanf (f_in, "%s", from);
      RAM.set (to, RAM.get (from)); //         TODO
    }

    else if (cmd == KW_PNT) {
      std_fscanf (f_in, "%s", name);
      printf ("%d\n", RAM.get (name));
    }

    else if (cmd == KW_SCN) {
      std_fscanf (f_in, "%s", name);
      scanf ("%d", &val);
      RAM.set (name, val); //                 TODO
    }

    else if (cmd == KW_SIG) {
      std_fscanf (f_in, "%s", name);
      sh_handler (name);
    }

    else if (cmd == KW_SET) {
      std_fscanf (f_in, "%s", name);
      std_fscanf (f_in, "%s", hex);
      if (!ishexstr (hex)) errret ("unknown char. must have hex.");
      RAM.set (name, strtoint (hex)); //        TODO
    }

    else errret ("End\n");
    std_fscanf (f_in, "%s", cmd);
  }


  fclose (f_in);

}
