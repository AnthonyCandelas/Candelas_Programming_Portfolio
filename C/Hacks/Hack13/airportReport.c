/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 08Dec2025
 * Lab/Task: Hack13 - Airport sorting and searching test driver
 *
 * Description:
 * Test driver that creates an array of at least 5 airports and
 * demonstrates the generateReports function which sorts and searches
 * the airport data in various ways.
 *
 * Notes:
 * - Demonstrates all required sorting/searching functionality.
 * - Uses representative airports from different locations.
 */

#include <stdlib.h>
#include <stdio.h>
#include "airport.h"

int main(void) {
  
  /* Create array with 6 diverse airports for testing */
  Airport airports[6];
  
  /* Omaha - close to Lincoln */
  initAirport(&airports[0], "OMA", "normal", "Eppley Airfield", 
              41.3030, -95.8940, 150, "Omaha", "US");
  
  /* Chicago - large hub */
  initAirport(&airports[1], "ORD", "huge", "O'Hare", 
              41.9742, -87.9073, 125, "Chicago", "US");
  
  /* Toronto - international */
  initAirport(&airports[2], "YYZ", "large_airport", "Pearson", 
              43.6, -79.6, 25, "Toronto", "CN");
  
  /* New York - to test city search */
  initAirport(&airports[3], "LGA", "international", "LaGuardia", 
              40.7769, -73.8740, 50, "New York", "US");
  
  /* Sydney - far from Lincoln */
  initAirport(&airports[4], "SYD", "large_airport", "Sydney Airport", 
              -33.9461, 151.1772, 21, "Sydney", "AU");
  
  /* London - European location */
  initAirport(&airports[5], "LHR", "large_airport", "Heathrow", 
              51.4700, -0.4543, 83, "London", "GB");
  
  /* Generate all reports */
  generateReports(airports, 6);
  
  return 0;
}
