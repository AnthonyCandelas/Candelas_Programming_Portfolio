/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 02Dec2025
 * Lab/Task: Lab13 - Sorting and Searching (Driver)
 *
 * Description:
 * Driver program demonstrating various sorting and searching
 * techniques over an array of Team structures. Reads data from the
 * CSV file and runs several sorts and searches, printing results.
 *
 * Notes:
 * - The program expects the CSV file at `../data/mlb_nl_2011.csv` by
 *   default; an alternative path may be passed as the first argument.
 */

/* Main driver program for the MLB team sorting and searching demo code. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <search.h>

#include "team.h"

extern int NUM_TEAMS;

int main(int argc, char **argv) {

  /* Default file path. */
  char *filePath = "../data/mlb_nl_2011.csv";
  if(argc == 2) {
    filePath = argv[1];
  }

  Team *teams = readCsvFile(filePath);

  if(teams == NULL) {
    fprintf(stderr, "Unable to process CSV file.\n");
    exit(1);
  }

  printf("Teams, original order: \n");
  printAllTeams(teams, NUM_TEAMS);

  printf("(Bubble) Sorted by win percentage: \n");
  bubbleSortTeams(teams, NUM_TEAMS, teamComparisonByWinPercentage);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Selection) Sorted by payroll: \n");
  selectionSortTeamsByPayroll(teams, NUM_TEAMS);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Selection with comparator) Sorted by payroll: \n");
  /* Use the payroll comparator (decreasing order) with selection sort. */
  selectionSortTeams(teams, NUM_TEAMS, teamComparisonByPayrollDesc);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Quick) Sorted by name: \n");
  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByName);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Quick) Sorted by win percentage: \n");
  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByWinPercentage);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Quick) Sorted by state (then city): \n");
  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByStateCity);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Quick) Sorted by payroll (increasing order): \n");
  /* Use qsort with payroll comparator (ascending order). */
  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByPayrollAsc);
  printAllTeams(teams, NUM_TEAMS);

  /* search, find */
  Team caKey;
  initTeam(&caKey, "", 0, 0, "", "CA", 0, 0);
  Team *caTeam = NULL;

  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByWinPercentage);
  caTeam = bsearch(&caKey, teams, NUM_TEAMS, sizeof(Team), teamComparisonByState);
  printf("Search #1 result for CA team (via state): \n");
  printTeam(caTeam);

  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByState);
  caTeam = bsearch(&caKey, teams, NUM_TEAMS, sizeof(Team), teamComparisonByState);
  printf("Search #2 result for CA team (via state): \n");
  printTeam(caTeam);

  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByStateCity);
  caTeam = bsearch(&caKey, teams, NUM_TEAMS, sizeof(Team), teamComparisonByState);
  printf("Search #3 result for CA team (via state): \n");
  printTeam(caTeam);

  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByWinPercentage);
  size_t elems = NUM_TEAMS;
  caTeam = lfind(&caKey, teams, &elems, sizeof(Team), teamComparisonByState);
  printf("Search #4 result for CA team (via state): \n");
  printTeam(caTeam);

  /* Search for the Cubs and print it out: */
  printf("Search result for Cubs (via name): \n");
  Team cubsKey;
  initTeam(&cubsKey, "Cubs", 0, 0, "", "", 0, 0);
  /* sort by name and use bsearch to find the Cubs */
  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByName);
  Team *found = bsearch(&cubsKey, teams, NUM_TEAMS, sizeof(Team), teamComparisonByName);
  if (found != NULL) {
    printTeam(found);
  } else {
    printf("Cubs not found\n");
  }

  return 0;
}
