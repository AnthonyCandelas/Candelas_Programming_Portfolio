
/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 02Dec2025
 * Lab/Task: Lab13 - Sorting and Searching (Team utilities)
 *
 * Description:
 * Declarations for the Team structure and related helper functions
 * used by the MLB sorting/searching demonstration. Includes factory
 * routines, printing utilities, and comparator prototypes used by
 * sorting/searching algorithms.
 *
 * Notes:
 * - Caller is responsible for freeing any memory allocated by
 *   initTeam/readCsvFile when appropriate.
 */
/* A basic structure to represent an MLB team. */
typedef struct {
  char *name;
  int wins;
  int loss;
  char *city;
  char *state;
  double payroll;
  double averageSalary;
} Team;

/**
 * A factory function to initialize a Team structure instance.
 */
void initTeam(Team *team, char *name, int wins, int loss, char *city, char *state,
                 double payroll, double aveSalary);

/**
 * Reads in Team data from the given file, returns
 * an array of Teams.
 */
Team *readCsvFile(const char *fileName);

/**
 * Prints a single team to the standard output.
 */
void printTeam(const Team *t);

/**
 * Prints an array of teams to the standard output.
 */
void printAllTeams(Team *teams, int size);

/**
 * An implementation of bubble sort that sorts the given teams
 * according to the given comparator.
 */
void bubbleSortTeams(Team *teams, int size,
                     int (*compar)(const void *, const void *));

/**
 * An implementation of selection sort that sorts the given teams
 * according to payroll in descending order.
 */
void selectionSortTeamsByPayroll(Team *teams, int size);

/**
 * An implementation of selection sort that sorts the given teams
 * according to the given comparator.
 */
void selectionSortTeams(Team *teams, int size,
                        int (*compar)(const void *, const void *));

/**
 * A comparator that orders Teams by name in lexicographic order.
 */
int teamComparisonByName(const void *s1, const void *s2);

/**
 * A comparator that orders Teams by win percentage (highest first)
 */
int teamComparisonByWinPercentage(const void *s1, const void *s2);

/**
 * A comparator that orders Teams by state.
 */
int teamComparisonByState(const void *s1, const void *s2);

/**
 * A comparator that orders Teams by state then by city.
 */
int teamComparisonByStateCity(const void *s1, const void *s2);

/* Comparator that orders Teams by payroll in decreasing order. */
int teamComparisonByPayrollDesc(const void *s1, const void *s2);

/* Comparator that orders Teams by payroll in increasing order. */
int teamComparisonByPayrollAsc(const void *s1, const void *s2);


