#
# makefile for this lab
#

# compiler and flags
CC = gcc
FLAGS = -Wall -g

# cURL library
CURL_LIB = -lcurl

# json-c library
JSON_INCLUDE = -I/usr/include/json-c/
JSON_LIB = -ljson-c

run: earthquakeReport.c earthquake.o utils.o
	$(CC) $(FLAGS) $(JSON_INCLUDE) -o run earthquakeReport.c utils.o earthquake.o $(CURL_LIB) $(JSON_LIB) -lm

earthquake.o: earthquake.c earthquake.h
	$(CC) $(FLAGS) $(JSON_INCLUDE) -c -o earthquake.o earthquake.c

utils.o: utils/utils.c utils/utils.h
	$(CC) $(FLAGS) $(JSON_INCLUDE) -c -o utils.o utils/utils.c

curlTest: utils.o earthquake.o
	$(CC) $(FLAGS) $(JSON_INCLUDE) -o curlTest utils.o earthquake.o tests/curlTest.c $(CURL_LIB) $(JSON_LIB) -lm

jsonTest: utils.o earthquake.o
	$(CC) $(FLAGS) $(JSON_INCLUDE) -o jsonTest utils.o earthquake.o tests/jsonTest.c $(CURL_LIB) $(JSON_LIB) -lm

clean:
	rm -f *.o *~
