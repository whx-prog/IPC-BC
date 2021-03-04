LIST:=$(wildcard *.c)
EXE:=$(LIST:%.c=%)
all:
	for i in $(EXE);do $(CC) $$i.c -o $$i;done
.PHONY:clean rebuild
rebuild:clean all
clean:
	$(RM) $(EXE) 
