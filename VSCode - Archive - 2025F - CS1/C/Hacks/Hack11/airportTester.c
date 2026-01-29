/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 17NOV2025
 * Lab/Task: Hack11 - Airport Tester
 *
 * Description:
 * Simple tester program that exercises the Airport API. Provides at
 * least three test cases for the main functions: creation/init,
 * airportToString, getAirDistance, and getEstimatedTravelTime.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"

/* Helper to print and free a string returned by airportToString */
static void showAndFree(char* s) {
  if (!s) return;
  printf("%s\n", s);
  free(s);
}

int main(void) {
  /* Create three well-known airports (approximate coords) */
  Airport* jfk = createAirport("KJFK", "large_airport", "John F Kennedy Intl", 40.6413, -73.7781, 13, "New York", "US");
  Airport* lax = createAirport("KLAX", "large_airport", "Los Angeles Intl", 33.9416, -118.4085, 125, "Los Angeles", "US");
  Airport* ord = createAirport("KORD", "large_airport", "Chicago O'Hare Intl", 41.9742, -87.9073, 672, "Chicago", "US");

  /* Test airportToString (3 cases) */
  char* s1 = airportToString(jfk);
  char* s2 = airportToString(lax);
  char* s3 = airportToString(ord);
  showAndFree(s1); showAndFree(s2); showAndFree(s3);

  /* Test getAirDistance (three pairwise distances) */
  double d_jfk_lax = getAirDistance(jfk, lax);
  double d_jfk_ord = getAirDistance(jfk, ord);
  double d_ord_lax = getAirDistance(ord, lax);
  printf("Distance JFK-LAX: %.2f km\n", d_jfk_lax);
  printf("Distance JFK-ORD: %.2f km\n", d_jfk_ord);
  printf("Distance ORD-LAX: %.2f km\n", d_ord_lax);

  /* Basic sanity checks (not a test harness) */
  if (d_jfk_lax <= 0.0 || d_jfk_ord <= 0.0 || d_ord_lax <= 0.0) {
    fprintf(stderr, "Distance computation error\n");
    return 2;
  }

  /* Test getEstimatedTravelTime with 3 stops (JFK -> ORD -> LAX) */
  Airport stops[3];
  /* Use initAirport to initialize stack-allocated records */
  initAirport(&stops[0], "KJFK", "large_airport", "John F Kennedy Intl", 40.6413, -73.7781, 13, "New York", "US");
  initAirport(&stops[1], "KORD", "large_airport", "Chicago O'Hare Intl", 41.9742, -87.9073, 672, "Chicago", "US");
  initAirport(&stops[2], "KLAX", "large_airport", "Los Angeles Intl", 33.9416, -118.4085, 125, "Los Angeles", "US");

  double estHours = getEstimatedTravelTime(stops, 3, 900.0, 1.0); /* 900 km/h, 1 hour layover */
  printf("Estimated travel time (JFK -> ORD -> LAX) at 900 km/h, 1h layover: %.2f hours\n", estHours);

  /* Additional tests: single-leg trip (size=2) and single stop (size=1) */
  double time_jfk_lax = getEstimatedTravelTime(stops, 2, 900.0, 1.0);
  double time_single = getEstimatedTravelTime(stops, 1, 900.0, 1.0);
  printf("Estimated travel time (JFK->ORD) at 900 km/h: %.2f hours\n", time_jfk_lax);
  printf("Estimated travel time (single stop): %.2f hours\n", time_single);

  /* Cleanup omitted: exiting now and letting the OS reclaim memory. */

  return 0;
}
