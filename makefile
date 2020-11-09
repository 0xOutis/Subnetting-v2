CC = gcc
CFLAGS = -c
LMFLAGS = -lm
OUTPUT = -o

subnet : main.o subnet.o
	$(CC) main.o subnet.o $(OUTPUT) subnet $(LMFLAGS)

main.o : main.c
	$(CC) $(CFLAGS) main.c

subnet.o : subnet.c subnet.h
	$(CC) $(CFLAGS) subnet.c

clean :
	rm -rf *.o subnet
