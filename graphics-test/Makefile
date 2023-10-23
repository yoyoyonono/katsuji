ALL_C = $(wildcard *.c) $(wildcard *.h)

all: $(ALL_C)
	cl65 -t cx16 -o MAIN.PRG -l main.list main.c

clean:
	rm -f *.PRG *.list *.o

exec: 
	/mnt/c/Users/athap/Downloads/x16emu_win64-r44/x16emu.exe -prg MAIN.PRG -run

run: clean all exec