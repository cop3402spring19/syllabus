all: classic getenvaddr

classic: classic.c
	gcc -fno-stack-protector -z execstack $< -o $@
	sudo chown root classic
	sudo chmod 4755 classic
	gcc -fno-stack-protector -z execstack $< -o $@.debug -g

getenvaddr: getenvaddr.c
	gcc $< -o $@

clean:
	rm -f classic.debug getenvaddr
	sudo rm -f classic
