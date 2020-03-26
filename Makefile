### Makefile todolist ###

todolist: todolist.o
	gcc -o todolist todolist.o -lm

limpar \ limpo:
	rm -f todolist todolist.o
