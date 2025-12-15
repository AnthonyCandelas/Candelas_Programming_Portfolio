/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 02Dec2025
 * Lab/Task: Lab13 - Sorting and Searching (Team implementations)
 *
 * Description:
 * Implementations for Team utilities: reading CSV data, printing,
 * simple sorting algorithms (bubble/select), and comparator
 * functions used by qsort/bsearch/lfind.
 *
 * Notes:
 * - The CSV reader allocates memory for strings stored in Team
 *   structures; callers should free them if necessary.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "team.h"

const int NUM_TEAMS = 16;

void initTeam(Team *t, char *name, int wins, int loss, char *city, char *state,
                 double payroll, double aveSalary) {
  t->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(t->name, name);
  t->wins = wins;
  t->loss = loss;
  t->city = (char *)malloc(sizeof(char) * (strlen(city) + 1));
  strcpy(t->city, city);
  t->state = (char *)malloc(sizeof(char) * (strlen(state) + 1));
  strcpy(t->state, state);
  t->payroll = payroll;
  t->averageSalary = aveSalary;

}

void printTeam(const Team *t) {
  if (t == NULL) {
    printf("null\n");
    return;
  }
  double winPerc = 100.0 * t->wins / (double)(t->wins + t->loss);
  printf("%-10s %3d  %3d (%5.2f) %-15s %2s $%12.2f $%9.2f\n", t->name, t->wins,
         t->loss, winPerc, t->city, t->state, t->payroll, t->averageSalary);
}

void printAllTeams(Team *teams, int size) {
  int i;
  printf("%-9s %-4s %-4s (%-4s) %-12s %-2s %-13s %-11s\n", "Name", "Wins",
           "Loss", "Win %", "City", "State", "Payroll", "Avg Salary");
  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
  for (i = 0; i < size; i++) {
    printTeam(&teams[i]);
  }
  printf("\n\n");
}

Team *readCsvFile(const char *fileName) {
  Team *teams = (Team *)malloc(sizeof(Team) * NUM_TEAMS);

  FILE *instream = fopen(fileName, "r");
  if (instream == NULL) {
    return NULL;
  }

  /* Read the file, line by line. */
  int i = 0;
  int size = 1000;
  char *tempBuffer = (char *)malloc(sizeof(char) * size);

  /* Discard first line (headers). */
  fgets(tempBuffer, size, instream);
  while (fgets(tempBuffer, size, instream) != NULL && i < NUM_TEAMS) {
    char name[100];
    int wins, loss;
    char *city, *state;
    double payroll, averageSalary;
    /* Remove the endline character from the line. */
    tempBuffer[strlen(tempBuffer) - 1] = '\0';
    char *teamToken = strtok(tempBuffer, ",");
    strcpy(name, teamToken);
    wins = atoi(strtok(NULL, ","));
    loss = atoi(strtok(NULL, ","));
    city = strtok(NULL, ",");
    state = strtok(NULL, ",");
    payroll = atof(strtok(NULL, ","));
    averageSalary = atof(strtok(NULL, ","));
    initTeam(&teams[i], name, wins, loss, city, state, payroll, averageSalary);
    i++;
  }
  fclose(instream);

  free(tempBuffer);

  return teams;
}

void bubbleSortTeams(Team *teams, int size,
                     int (*compar)(const void *, const void *)) {
  int i, j;
  Team temp;
  for (i = 0; i < size - 1; i++) {
    for (j = 0; j < size - 1; j++) {
      /* Compare adjacent teams by asking the comparator function
         passed in; if out of order, swap them. */
      if (compar(&teams[j], &teams[j + 1]) > 0) {
        temp = teams[j];
        teams[j] = teams[j + 1];
        teams[j + 1] = temp;
      }
    }
  }
}

void selectionSortTeamsByPayroll(Team *teams, int size) {
  /* Selection sort ordering teams by payroll in decreasing order. */
  int i, j, max_idx;
  for (i = 0; i < size - 1; ++i) {
    max_idx = i;
    for (j = i + 1; j < size; ++j) {
      if (teams[j].payroll > teams[max_idx].payroll) {
        max_idx = j;
      }
    }
    if (max_idx != i) {
      Team tmp = teams[i];
      teams[i] = teams[max_idx];
      teams[max_idx] = tmp;
    }
  }
}

void selectionSortTeams(Team *teams, int size,
                        int (*compar)(const void *, const void *)) {
  /* Generic selection sort using the provided comparator. */
  int i, j, min_idx;
  for (i = 0; i < size - 1; ++i) {
    min_idx = i;
    for (j = i + 1; j < size; ++j) {
      if (compar(&teams[j], &teams[min_idx]) < 0) {
        min_idx = j;
      }
    }
    if (min_idx != i) {
      Team tmp = teams[i];
      teams[i] = teams[min_idx];
      teams[min_idx] = tmp;
    }
  }
}

int teamComparisonByName(const void *s1, const void *s2) {
  const Team *t1 = (const Team *)s1;
  const Team *t2 = (const Team *)s2;
  int result = strcmp(t1->name, t2->name);
  return result;
}

int teamComparisonByState(const void *s1, const void *s2) {
  const Team *t1 = (const Team *)s1;
  const Team *t2 = (const Team *)s2;
  return strcmp(t1->state, t2->state);
}

int teamComparisonByStateCity(const void *s1, const void *s2) {
  const Team *t1 = (const Team *)s1;
  const Team *t2 = (const Team *)s2;
  int result = strcmp(t1->state, t2->state);
  if (result == 0) {
    result = strcmp(t1->city, t2->city);
  }
  return result;
}

int teamComparisonByWinPercentage(const void *s1, const void *s2) {
  const Team *t1 = (const Team *)s1;
  const Team *t2 = (const Team *)s2;
  double t1_winPer = t1->wins / (double)(t1->wins + t1->loss);
  double t2_winPer = t2->wins / (double)(t2->wins + t2->loss);

  if (t1_winPer < t2_winPer) {
    return 1;
  } else if (t1_winPer > t2_winPer) {
    return -1;
  } else {
    return 0;
  }
}

/* Comparator ordering Teams by payroll in descending order. */
int teamComparisonByPayrollDesc(const void *s1, const void *s2) {
  const Team *t1 = (const Team *)s1;
  const Team *t2 = (const Team *)s2;
  if (t1->payroll < t2->payroll) return 1;
  if (t1->payroll > t2->payroll) return -1;
  return 0;
}

/* Comparator ordering Teams by payroll in increasing (ascending) order. */
int teamComparisonByPayrollAsc(const void *s1, const void *s2) {
  const Team *t1 = (const Team *)s1;
  const Team *t2 = (const Team *)s2;
  if (t1->payroll < t2->payroll) return -1;
  if (t1->payroll > t2->payroll) return 1;
  return 0;
}
