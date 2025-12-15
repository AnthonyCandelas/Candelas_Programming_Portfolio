CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c11 -g
LDFLAGS := -lm
CMOCKA := -lcmocka

TARGETS := kaprekarDemo kaprekarTest kaprekarTestCmocka

all: $(TARGETS)

kaprekar_utils.o: kaprekar_utils.c kaprekar_utils.h
	$(CC) $(CFLAGS) -c kaprekar_utils.c -o kaprekar_utils.o

kaprekarDemo: kaprekar_utils.o kaprekar_demo.c
	$(CC) $(CFLAGS) kaprekar_demo.c kaprekar_utils.o $(LDFLAGS) -o $@

kaprekarTest: kaprekar_utils.o kaprekar_test.c
	$(CC) $(CFLAGS) kaprekar_test.c kaprekar_utils.o $(LDFLAGS) -o $@

kaprekarTestCmocka: kaprekar_utils.o kaprekar_test_cmocka.c
	$(CC) $(CFLAGS) kaprekar_test_cmocka.c kaprekar_utils.o $(LDFLAGS) $(CMOCKA) -o $@

clean:
	rm -f *.o $(TARGETS) *~ *.dSYM
