main: proc asm
	echo "Done"

proc: proc.cpp
	g++ proc.cpp -o proc

asm: asm.cpp
	g++ asm.cpp -o asm

clean:
	rm -f *.o

uninstall: clean
	rm ./asm
	rm ./proc
