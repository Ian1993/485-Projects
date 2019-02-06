  all: SeaShell.c
	gcc -g -Wall -o SeaShell SeaShell.c

  clean: 
	  $(RM) SeaShell
