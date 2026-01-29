#/*******************
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 2025-11-04
 * Lab/Task: Lab10
 *
 * Description:
 * This program processes a CSV file of data on major league
 * baseball teams, sorts them according to win percentage and
 * prints them to the standard output.
 *
 *******************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * A sorting function to sort the teams and their win percentages
 * using the selection sort algorithm which successively finds the
 * "maximum" element and places it at the front of the array
 */
void sortMLB(char **teams, double *winPerc, int numTeams);

/**
 * This function prints the given teams with win percentages
 * to the standard output.
 */
void printMLB(char **teams, double *winPerc, int numTeams);

int main(int argc, char **argv) {
  (void)argc; (void)argv; /* mark unused to avoid compiler warnings */
  int const maxSize = 50;
  int const numTeams = 16;
  char filePath[] = "data/mlb_nl_2011.txt";
  char tempBuffer[100];

  int i;
  char **teams = (char **)malloc(sizeof(char *) * numTeams);
  double *winPercentages = (double *)malloc(sizeof(double) * numTeams);
  for (i = 0; i < numTeams; i++) {
    teams[i] = (char *)malloc(sizeof(char) * maxSize);
  }

  
  FILE *instream = fopen(filePath, "r");
  if (instream == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", filePath);
    return 1;
  }

  i = 0;
  while (fgets(tempBuffer, sizeof(tempBuffer), instream) != NULL && i < numTeams) {
    size_t len = strlen(tempBuffer);
    if (len > 0 && (tempBuffer[len - 1] == '\n' || tempBuffer[len -1] == '\r')) {
      tempBuffer[len - 1] = '\0';
      len--;
    }
    char *token = strtok(tempBuffer, " \t\n");
    if (token == NULL) {
      continue;
    }
    strncpy(teams[i], token, maxSize - 1);
    teams[i][maxSize - 1] = '\0';
    
    token = strtok(NULL, " \t\n");
    if (token == NULL) {
      fprintf(stderr, "Malformed line (missing wins): %s\n", tempBuffer);
      continue;
    }
    int wins = atoi(token);
    token = strtok(NULL, " \t\n");
    if (token == NULL) {
      fprintf(stderr, "Malformed line (missing losses): %s\n", tempBuffer);
      continue;
    }
    int losses = atoi(token);
    int totalGames = wins + losses;
    if (totalGames > 0) {
      winPercentages[i] = ((double)wins) / ((double)totalGames);
    } else {
      winPercentages[i] = 0.0;
    }
    i++;
  }
  fclose(instream);

  sortMLB(teams, winPercentages, i);
  printMLB(teams, winPercentages, i);

  for (int k = 0; k < i; k++) {
    free(teams[k]);
  }
  free(teams);
  free(winPercentages);

  return 0;
}

void sortMLB(char **teams, double *winPerc, int numTeams) {
  int i, j, max_index;
  char tmp_str[100];
  double tmp_dbl;
  for (i = 0; i < numTeams - 1; i++) {
    max_index = i;
    for (j = i + 1; j < numTeams; j++) {
      if (winPerc[max_index] < winPerc[j]) {
        max_index = j;
      }
    }
    /* swap the ith element and the maximum element (swap both arrays) */
    if(i != max_index) {
      tmp_dbl = winPerc[i];
      winPerc[i] = winPerc[max_index];
      winPerc[max_index] = tmp_dbl;
      strcpy(tmp_str, teams[i]);
      strcpy(teams[i], teams[max_index]);
      strcpy(teams[max_index], tmp_str);
    }
  }
}

void printMLB(char **teams, double *winPerc, int numTeams) {
  int i = 0;
  printf("%-12s %-10s\n", "TEAM", "WIN PERC");
  for (i = 0; i < numTeams; i++) {
    printf("%-12s %.3f\n", teams[i], winPerc[i]);
  }
}
