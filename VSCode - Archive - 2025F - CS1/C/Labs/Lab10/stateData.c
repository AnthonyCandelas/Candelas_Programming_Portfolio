#/*******************
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 2025-11-04
 * Lab/Task: Lab10
 *
 * Description:
 * This program processes a CSV file containing data on US
 * States and produces an XML-formatted file with the same data.
 *
 *******************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * This function takes an array of states (names as strings) and
 * an array of each one's population and outputs them to an XML-formatted
 * file.
 */
void toXMLFile(char **states, int *populations, int numStates);

/**
 * This function trims trailing whitespace from the given string.
 */
void rtrim(char *str);

int main(int argc, char **argv) {
  (void)argc; (void)argv; /* mark unused to avoid compiler warnings */
  int const size = 200;
  int const numStates = 50;
  char filePath[] = "data/stateData.txt";
  char tempBuffer[size];

  
  int i;
  char **states = (char **)malloc(sizeof(char *) * numStates);
  int *statePopulations = (int *)malloc(sizeof(int) * numStates);
  for (i = 0; i < numStates; i++) {
    states[i] = (char *)malloc(sizeof(char) * size);
  }

  
  FILE *instream = fopen(filePath, "r");
  if (instream == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", filePath);
    exit(1);
  }

  
  i = 0;
  while (fgets(tempBuffer, size, instream) != NULL) {
    tempBuffer[strlen(tempBuffer) - 1] = '\0';
    char *stateToken = strtok(tempBuffer, ",");
    strcpy(states[i], stateToken);
    char *popToken = strtok(NULL, ",");
    statePopulations[i] = atoi(popToken);
    i++;
  }
  fclose(instream);

  
  int total = 0;
  for (i = 0; i < numStates; i++) {
    printf("%15s %10d\n", states[i], statePopulations[i]);
    total += statePopulations[i];
  }
  printf("%-15s  %10d\n", "TOTAL", total);

  
  FILE *outstream = fopen("data/stateData.dat", "wb");
  if (outstream == NULL) {
    fprintf(stderr, "Unable to create binary file: data/stateData.dat\n");
    exit(1);
  }
  for (i = 0; i < numStates; i++) {
    fwrite(states[i], sizeof(char), 15, outstream);
    fwrite(&statePopulations[i], sizeof(int), 1, outstream);
  }
  fclose(outstream);

  toXMLFile(states, statePopulations, 50);

  for (i = 0; i < numStates; i++) {
    free(states[i]);
  }
  free(states);
  free(statePopulations);

  return 0;
}

void toXMLFile(char **states, int *populations, int numStates) {
  FILE *out = fopen("data/stateData.xml", "w");
  if (out == NULL) {
    fprintf(stderr, "Unable to create XML file: data/stateData.xml\n");
    return;
  }

  fprintf(out, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(out, "<STATES>\n");
  int i;
  for (i = 0; i < numStates; i++) {
    rtrim(states[i]);
    fprintf(out, "  <STATE>\n");
    fprintf(out, "    <NAME>%s</NAME>\n", states[i]);
    fprintf(out, "    <POPULATION>%d</POPULATION>\n", populations[i]);
    fprintf(out, "  </STATE>\n");
  }
  fprintf(out, "</STATES>\n");
  fclose(out);
}

void rtrim(char *str) {
  int n = strlen(str);
  while (n >= 0 && isspace(str[n - 1])) {
    str[n - 1] = '\0';
    n--;
  }
  return;
}
