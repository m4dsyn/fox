main: proc asm disasm
	echo "Done"

proc: defines proc.cpp
	g++ proc.cpp -o proc

asm: defines asm.cpp
	g++ asm.cpp -o asm

disasm: defines disasm.cpp defines
	g++ disasm.cpp -o disasm

defines: defines.h registers.h memory.h core.h signal.h number.h

clean:
	rm -f *.o

uninstall: clean
	rm ./asm
	rm ./proc
	rm ./disasm
