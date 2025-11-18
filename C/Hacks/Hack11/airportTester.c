/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 17Nov2025
 * Lab/Task: Hack11 - Airport tester
 *
 * Tester: exercises createAirport, initAirport, airportToString,
 * getAirDistance and getEstimatedTravelTime with labeled test cases.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "airport.h"

/* Helper to print a test header */
static void header(const char* s) {
	printf("\n=== %s ===\n", s);
}

int main(void) {
	/* Test group 1: createAirport (heap) - three cases */
	header("createAirport tests");
	Airport* jfk = createAirport("KJFK", "large_airport", "John F. Kennedy International Airport",
															 40.6413, -73.7781, 13, "Queens", "US");
	Airport* lax = createAirport("KLAX", "large_airport", "Los Angeles International Airport",
															 33.9416, -118.4085, 125, "Los Angeles", "US");
	Airport* ord = createAirport("KORD", "large_airport", "O'Hare International Airport",
															 41.9742, -87.9073, 672, "Chicago", "US");

	char* s1 = airportToString(jfk);
	char* s2 = airportToString(lax);
	char* s3 = airportToString(ord);
	printf("[case 1] %s\n", s1 ? s1 : "(null)");
	printf("[case 2] %s\n", s2 ? s2 : "(null)");
	printf("[case 3] %s\n", s3 ? s3 : "(null)");
	free(s1); free(s2); free(s3);

	/* Test group 2: initAirport (stack) - three cases */
	header("initAirport tests");
	Airport a1, a2, a3;
	initAirport(&a1, "KSFO", "large_airport", "San Francisco International Airport",
							37.6213, -122.3790, 13, "San Francisco", "US");
	initAirport(&a2, "KSAN", "medium_airport", "San Diego International Airport",
							32.7338, -117.1933, 17, "San Diego", "US");
	initAirport(&a3, "KSEA", "large_airport", "Seattle-Tacoma International Airport",
							47.4502, -122.3088, 433, "Seattle", "US");
	char* t1 = airportToString(&a1);
	char* t2 = airportToString(&a2);
	char* t3 = airportToString(&a3);
	printf("[case 1] %s\n", t1 ? t1 : "(null)");
	printf("[case 2] %s\n", t2 ? t2 : "(null)");
	printf("[case 3] %s\n", t3 ? t3 : "(null)");
	free(t1); free(t2); free(t3);

	/* Test group 3: getAirDistance - three cases */
	header("getAirDistance tests");
	double d_jfk_lax = getAirDistance(jfk, lax);
	double d_lax_sfo = getAirDistance(lax, &a1); /* LAX -> SFO */
	double d_same = getAirDistance(jfk, jfk);
	printf("[case 1] JFK -> LAX = %.2f km\n", d_jfk_lax);
	printf("[case 2] LAX -> SFO = %.2f km\n", d_lax_sfo);
	printf("[case 3] JFK -> JFK = %.2f km\n", d_same);

	/* Test group 4: getEstimatedTravelTime - three cases */
	header("getEstimatedTravelTime tests");
	/* case 1: direct flight JFK -> LAX */
	Airport directStops1[2];
	initAirport(&directStops1[0], jfk->gpsId, jfk->type, jfk->name, jfk->latitude, jfk->longitude, jfk->elevationFeet, jfk->city, jfk->countryAbbrv);
	initAirport(&directStops1[1], lax->gpsId, lax->type, lax->name, lax->latitude, lax->longitude, lax->elevationFeet, lax->city, lax->countryAbbrv);
	double t_direct = getEstimatedTravelTime(directStops1, 2, 900.0, 1.0);
	printf("[case 1] JFK -> LAX @900km/h = %.2f hours\n", t_direct);

	/* case 2: JFK -> ORD -> LAX with 1 hour layover */
	Airport multiStops[3];
	initAirport(&multiStops[0], jfk->gpsId, jfk->type, jfk->name, jfk->latitude, jfk->longitude, jfk->elevationFeet, jfk->city, jfk->countryAbbrv);
	initAirport(&multiStops[1], ord->gpsId, ord->type, ord->name, ord->latitude, ord->longitude, ord->elevationFeet, ord->city, ord->countryAbbrv);
	initAirport(&multiStops[2], lax->gpsId, lax->type, lax->name, lax->latitude, lax->longitude, lax->elevationFeet, lax->city, lax->countryAbbrv);
	double t_multi = getEstimatedTravelTime(multiStops, 3, 900.0, 1.0);
	printf("[case 2] JFK -> ORD -> LAX @900km/h, 1hr layover = %.2f hours\n", t_multi);

	/* case 3: invalid input (size=1) should be 0 */
	double t_none = getEstimatedTravelTime(&a1, 1, 900.0, 1.0);
	printf("[case 3] single stop = %.2f hours\n", t_none);

	/* cleanup: free heap allocations */
	freeAirport(jfk);
	freeAirport(lax);
	freeAirport(ord);

	/* free strings inside stack-initialized airports */
	free(a1.gpsId); free(a1.type); free(a1.name); free(a1.city); free(a1.countryAbbrv);
	free(a2.gpsId); free(a2.type); free(a2.name); free(a2.city); free(a2.countryAbbrv);
	free(a3.gpsId); free(a3.type); free(a3.name); free(a3.city); free(a3.countryAbbrv);
	free(directStops1[0].gpsId); free(directStops1[0].type); free(directStops1[0].name); free(directStops1[0].city); free(directStops1[0].countryAbbrv);
	free(directStops1[1].gpsId); free(directStops1[1].type); free(directStops1[1].name); free(directStops1[1].city); free(directStops1[1].countryAbbrv);
	free(multiStops[0].gpsId); free(multiStops[0].type); free(multiStops[0].name); free(multiStops[0].city); free(multiStops[0].countryAbbrv);
	free(multiStops[1].gpsId); free(multiStops[1].type); free(multiStops[1].name); free(multiStops[1].city); free(multiStops[1].countryAbbrv);
	free(multiStops[2].gpsId); free(multiStops[2].type); free(multiStops[2].name); free(multiStops[2].city); free(multiStops[2].countryAbbrv);

	return 0;
}

