#include <stdlib.h>
#include <stdio.h>

#include "student.h"

/**
 * Student structure demonstration program
 */
int main(int argc, char **argv) {

  Student *me = createStudent("Anthony", "Candelas", 24353131, "07/14/1993");
  printStudent(me);

  //create a roster of students
  Student roster[3];
  initStudent(&roster[0], "Alan", "Turing", 12345678, "06/23/1912");
  initStudent(&roster[1], "Grace", "Hopper", 87654321, "12/09/1906");
  initStudent(&roster[2], "Brian", "Kernighan", 11223344, "01/30/1942");

  printf("Roster\n");
  printf("==========================\n");
  for(int i=0; i<3; i++) {
    printStudent(&roster[i]);
  }

}
