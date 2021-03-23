CC = gcc
CFLAGS = -c
OFLAGS = -o

subnet : main.o subnet.o
	$(CC) main.o subnet.o $(OFLAGS) subnet

main.o : main.c
	$(CC) $(CFLAGS) main.c

subnet.o : subnet.c subnet.h
	$(CC) $(CFLAGS) subnet.c

clean :
	rm -rf *.o subnet
