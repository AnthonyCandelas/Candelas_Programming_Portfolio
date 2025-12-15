CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c11 -g
LDFLAGS := -lcurl

all: battleship

battleship: battleship_client.c
	$(CC) $(CFLAGS) battleship_client.c $(LDFLAGS) -o battleship

clean:
	rm -f battleship *.o *~ *.dSYM
