a.out:StackQueue.c maze.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm a.out
