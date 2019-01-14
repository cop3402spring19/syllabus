all: run

run: factorial.o run.o
	gcc -o $@ $^
	# gcc -o run factorial.o run.o

factorial.o: factorial.c
	gcc -c factorial.c

run.o: run.c
	gcc -c run.c

clean:
	rm -f run factorial.o run.o
