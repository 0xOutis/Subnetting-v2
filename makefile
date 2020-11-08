CC = gcc
CFLAGS = -c
CFLAGSS = -lm

subnet : main.o subnet.o
	$(CC) main.o subnet.o -o subnet $(CFLAGSS)

main.o : main.c
	$(CC) $(CFLAGS) main.c

subnet.o : subnet.c subnet.h
	$(CC) $(CFLAGS) subnet.c

clean :
	rm -rf *.o subnet
