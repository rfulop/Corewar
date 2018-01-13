#Corewar
A virtual “arena” in which programs will fight against one another (the “Champions”) and an assembler to those Champions as well as a Champion to show the world that you can create life from coffee.

## Project Overview
I worked on this project with Loic Chety, Anna Maciejewicz and Mike Lambert for École 42.
At the root of this repository you will find a pdf file with, among other things, a description of the instructions, and the rules of the virtual machine.
We created three programs, the assembler, that compiles champions into bytecode, a decompiler, and the virtual machine, that runs those champions against each other.
We got the highest grade on this project (118%).

## Installing
You need the ncurses library for runing the Makefile.
```
make 
```

### The Assembler (asm)
The assembler takes .s files as arguments and, if they possess valid instructions creates the corresponding .cor file which will then be used as an argument for the virtual machine.
```
Usage : ./asm [-[+]hvd] {*.cor}
Options :
h : Print help
v : Verbose Mode
d : Debug Mode
```

### The Decompiler
The decompiler takes .cor files as arguments and generate the corresponding asm code on a .s file.
```
Usage : ./decompiler {*.cor}
```

### The Virtual Machine (corewar) 
The virtual machine takes as arguments 1 to 4 champions, loads them to the memory, and attributes one process to each. When there are no longer any processes alive the vm checks which was the last champion to execute the live instruction, and declares that champion to have won.
We have also implement a graphical mode, using the ncurses library and many verbose options.
```
Usage: ./corewar [-d N -v N | -ncurses ] <[-n N] champion1.cor> <...>
  -d N		: Dumps memory after N cycles then exits
  -v N		: Verbosity levels, can be added together to enable several
			- 0 : Show only essentials
			- 1 : Show lives
			- 2 : Show cycles
			- 4 : Show operations (Params are NOT litteral ...)
			- 8 : Show deaths
			- 16 : Show PC movements (Except for jumps)
  -ncurses	: Ncurses output mode
  -n N		: Champion number (position at initalisation of memory)
```
