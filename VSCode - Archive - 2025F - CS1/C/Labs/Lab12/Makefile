CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2

TARGETS = jacobsthal jacobsthalMemoization palindrome

.PHONY: all clean clean-windows

all: $(TARGETS)

jacobsthal: jacobsthal.c
	$(CC) $(CFLAGS) -o jacobsthal jacobsthal.c

jacobsthalMemoization: jacobsthalMemoization.c
	$(CC) $(CFLAGS) -o jacobsthalMemoization jacobsthalMemoization.c

palindrome: palindrome.c
	$(CC) $(CFLAGS) -o palindrome palindrome.c

clean:
	rm -f $(TARGETS) *.o *~

clean-windows:
	del /Q jacobsthal.exe jacobsthalMemoization.exe palindrome.exe 2>NUL || true
