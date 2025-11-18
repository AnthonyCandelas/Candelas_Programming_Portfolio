/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 17Nov2025
 * Lab/Task: Hack11 - Airport utilities
 *
 * Description:
 * Implements Airport creation, formatting, distance and travel-time
 * utilities required by the Hack11 assignment.
 */

#include "airport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Helper: duplicate string safely (returns NULL if src NULL). */
static char* strCopy(const char* src) {
  if (!src) return NULL;
  char* s = strdup(src);
  return s;
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
  airport->gpsId = strCopy(gpsId);
  airport->type = strCopy(type);
  airport->name = strCopy(name);
  airport->latitude = latitude;
  airport->longitude = longitude;
  airport->elevationFeet = elevationFeet;
  airport->city = strCopy(city);
  airport->countryAbbrv = strCopy(countryAbbrv);
}

Airport* createAirport(const char* gpsId,
                       const char* type,
                       const char* name,
                       double latitude,
                       double longitude,
                       int elevationFeet,
                       const char* city,
                       const char* countryAbbrv) {
  Airport* a = malloc(sizeof(Airport));
  if (!a) return NULL;
  initAirport(a, gpsId, type, name, latitude, longitude, elevationFeet, city, countryAbbrv);
  return a;
}

void freeAirport(Airport* a) {
  if (!a) return;
  free(a->gpsId);
  free(a->type);
  free(a->name);
  free(a->city);
  free(a->countryAbbrv);
  free(a);
}

char* airportToString(const Airport* a) {
  if (!a) return NULL;
  /* produce a string: "GPSID (type): name — city, country [lat, lon] elev ft" */
  const char* gps = a->gpsId ? a->gpsId : "";
  const char* type = a->type ? a->type : "";
  const char* name = a->name ? a->name : "";
  const char* city = a->city ? a->city : "";
  const char* country = a->countryAbbrv ? a->countryAbbrv : "";

  char buf[512];
  int n = snprintf(buf, sizeof(buf), "%s (%s): %s — %s, %s [%.6f, %.6f] %d ft",
                   gps, type, name, city, country, a->latitude, a->longitude, a->elevationFeet);
  if (n < 0) return NULL;
  char* out = malloc((size_t)n + 1);
  if (!out) return NULL;
  memcpy(out, buf, (size_t)n + 1);
  return out;
}

/* Convert degrees to radians. */
static double deg2rad(double deg) {
  return deg * M_PI / 180.0;
}

double getAirDistance(const Airport* origin, const Airport* destination) {
  if (!origin || !destination) return 0.0;
  double phi1 = deg2rad(origin->latitude);
  double phi2 = deg2rad(destination->latitude);
  double deltaLambda = deg2rad(destination->longitude - origin->longitude);
  /* spherical law of cosines */
  double cosval = sin(phi1) * sin(phi2) + cos(phi1) * cos(phi2) * cos(deltaLambda);
  /* clamp to [-1,1] to avoid NaN from rounding */
  if (cosval > 1.0) cosval = 1.0;
  if (cosval < -1.0) cosval = -1.0;
  double central = acos(cosval);
  const double R = 6371.0; /* km */
  return central * R;
}

double getEstimatedTravelTime(const Airport* stops,
                              int size,
                              double aveKmsPerHour,
                              double aveLayoverTimeHrs) {
  if (!stops || size < 1 || aveKmsPerHour <= 0.0) return 0.0;
  if (size == 1) return 0.0; /* no travel needed */
  double totalHours = 0.0;
  for (int i = 0; i < size - 1; ++i) {
    double dist = getAirDistance(&stops[i], &stops[i+1]);
    totalHours += dist / aveKmsPerHour;
  }
  /* add layover times for intermediate stops (size-2 layovers) */
  if (size > 2 && aveLayoverTimeHrs > 0.0) {
    totalHours += (size - 2) * aveLayoverTimeHrs;
  }
  return totalHours;
}
