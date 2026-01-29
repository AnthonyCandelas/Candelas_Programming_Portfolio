/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 17NOV2025
 * Lab/Task: Hack11 - Airport Utilities
 *
 * Description:
 * Implements an Airport structure and utility functions to create,
 * initialize, stringify, and compute air distances / travel times
 * between airports using latitude/longitude values.
 *
 * NOTE: Functions that allocate memory (createAirport, airportToString)
 * return malloc'd memory; caller is responsible for free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Some Windows/mingw environments do not define M_PI by default */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "airport.h"

/* Internal definition of the Airport structure */
struct _Airport {
  char* gpsId;
  char* type;
  char* name;
  double latitude;
  double longitude;
  int elevationFeet;
  char* city;
  char* countryAbbrv;
};

/* Helper: duplicate string safely (returns malloc'd copy or NULL) */
static char* dupString(const char* s) {
  if (s == NULL) return NULL;
  size_t n = strlen(s) + 1;
  char* out = (char*)malloc(n);
  if (!out) return NULL;
  memcpy(out, s, n);
  return out;
}

/* Helper: convert degrees to radians */
static double deg2rad(double deg) {
  return deg * M_PI / 180.0;
}

/* Helper: clamp value to [-1,1] to avoid NaN from acos due to fp error */
static double clamp_unit(double v) {
  if (v > 1.0) return 1.0;
  if (v < -1.0) return -1.0;
  return v;
}

Airport* createAirport(const char* gpsId,
                       const char* type,
                       const char* name,
                       double latitude,
                       double longitude,
                       int elevationFeet,
                       const char* city,
                       const char* countryAbbrv) {
  struct _Airport* a = (struct _Airport*)malloc(sizeof(struct _Airport));
  if (!a) return NULL;
  a->gpsId = NULL; a->type = NULL; a->name = NULL; a->city = NULL; a->countryAbbrv = NULL;
  initAirport((Airport*)a, gpsId, type, name, latitude, longitude, elevationFeet, city, countryAbbrv);
  return (Airport*)a;
}

void initAirport(Airport* airport,
                 const char* gpsId,
                 const char* type,
                 const char* name,
                 double latitude,
                 double longitude,
                 int elevationFeet,
                 const char* city,
                 const char* countryAbbrv) {
  if (!airport) return;
  struct _Airport* a = (struct _Airport*)airport;

    /* NOTE: initAirport assumes the caller manages lifetime of existing
      storage. This function initializes fields by making deep copies. */
    a->gpsId = dupString(gpsId);
  a->type = dupString(type);
  a->name = dupString(name);
  a->latitude = latitude;
  a->longitude = longitude;
  a->elevationFeet = elevationFeet;
  a->city = dupString(city);
  a->countryAbbrv = dupString(countryAbbrv);
}

char* airportToString(const Airport* ap) {
  if (!ap) return NULL;
  const struct _Airport* a = (const struct _Airport*)ap;
  /* Estimate needed buffer size via snprintf with NULL */
  const char* fmt = "GPS: %s\nName: %s\nType: %s\nLatitude: %.6f\nLongitude: %.6f\nElevation (ft): %d\nCity: %s\nCountry: %s\n";
  int needed = snprintf(NULL, 0, fmt,
                        a->gpsId?a->gpsId:"(null)",
                        a->name?a->name:"(null)",
                        a->type?a->type:"(null)",
                        a->latitude,
                        a->longitude,
                        a->elevationFeet,
                        a->city?a->city:"(null)",
                        a->countryAbbrv?a->countryAbbrv:"(null)");
  if (needed < 0) return NULL;
  char* out = (char*)malloc((size_t)needed + 1);
  if (!out) return NULL;
  snprintf(out, (size_t)needed + 1, fmt,
           a->gpsId?a->gpsId:"(null)",
           a->name?a->name:"(null)",
           a->type?a->type:"(null)",
           a->latitude,
           a->longitude,
           a->elevationFeet,
           a->city?a->city:"(null)",
           a->countryAbbrv?a->countryAbbrv:"(null)");
  return out;
}

double getAirDistance(const Airport* origin, const Airport* destination) {
  if (!origin || !destination) return 0.0;
  const struct _Airport* a = (const struct _Airport*)origin;
  const struct _Airport* b = (const struct _Airport*)destination;

  double phi1 = deg2rad(a->latitude);
  double phi2 = deg2rad(b->latitude);
  double deltaLambda = deg2rad(b->longitude - a->longitude);

  double cosval = sin(phi1) * sin(phi2) + cos(phi1) * cos(phi2) * cos(deltaLambda);
  cosval = clamp_unit(cosval);
  double R = 6371.0; /* kilometers */
  double d = acos(cosval) * R;
  return d;
}

double getEstimatedTravelTime(const Airport* stops,
                              int size,
                              double aveKmsPerHour,
                              double aveLayoverTimeHrs) {
  if (!stops || size <= 1) return 0.0;
  if (aveKmsPerHour <= 0.0) return 0.0;

  double totalDistance = 0.0;
  const struct _Airport* arr = (const struct _Airport*)stops;
  for (int i = 0; i < size - 1; ++i) {
    totalDistance += getAirDistance((const Airport*)&arr[i], (const Airport*)&arr[i+1]);
  }

  double flightHours = totalDistance / aveKmsPerHour;
  int numLayovers = (size > 2) ? (size - 2) : 0;
  double totalLayoverHours = numLayovers * aveLayoverTimeHrs;
  return flightHours + totalLayoverHours;
}

/* Note: There is no public destructor in the header. If the caller wants
 * to free a created Airport, they should free the pointer and its fields
 * appropriately. Provide an internal helper here for tester convenience. */
static void freeAirportInternal(Airport* ap) {
  if (!ap) return;
  struct _Airport* a = (struct _Airport*)ap;
  free(a->gpsId); free(a->type); free(a->name); free(a->city); free(a->countryAbbrv);
  free(a);
}

/* Public cleanup functions */
void freeAirport(Airport* a) {
  freeAirportInternal(a);
}

void freeAirportFields(Airport* a) {
  if (!a) return;
  struct _Airport* p = (struct _Airport*)a;
  free(p->gpsId); p->gpsId = NULL;
  free(p->type); p->type = NULL;
  free(p->name); p->name = NULL;
  free(p->city); p->city = NULL;
  free(p->countryAbbrv); p->countryAbbrv = NULL;
}
