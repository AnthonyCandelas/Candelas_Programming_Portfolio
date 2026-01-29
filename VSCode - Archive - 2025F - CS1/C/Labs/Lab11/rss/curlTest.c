/**
 * A stand alone test utility for the 
 * libcurl library.  Provide a URL as a
 * command line argument and it will print
 * the response.
 */
#include <stdlib.h>
#include <stdio.h>

#include "curl_utils.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s url\n", argv[0]);
    exit(1);
  }
  char *result = getContent(argv[1]);
  printf("result = \n%s\n", result);
  return 0;
}
