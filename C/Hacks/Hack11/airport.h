/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 17Nov2025
 * Lab/Task: Hack11 - Airport utilities
 *
 * Description:
 * Provides an Airport structure and utility functions for
 * creating airports, formatting them as strings, and computing
 * air distances and estimated travel times.
 *
 * Notes:
 * - Functions that return allocated memory document that the
 *   caller is responsible for calling free() on the returned pointer.
 */

#ifndef HACK11_AIRPORT_H
#define HACK11_AIRPORT_H

#include <stddef.h>

typedef struct Airport {
  char* gpsId;        /* unique identifier (deep-copied) */
  char* type;         /* airport type (deep-copied) */
  char* name;         /* airport name (deep-copied) */
  double latitude;    /* degrees, -90..90 */
  double longitude;   /* degrees, -180..180 */
  int elevationFeet;  /* whole feet above sea level */
  char* city;         /* municipality (deep-copied) */
  char* countryAbbrv; /* country abbreviation (deep-copied) */
} Airport;

/* A factory function to create a new Airport with deep copies
 * of the given string attributes. Returns NULL on allocation
 * failure. The caller is responsible for freeing the returned
 * Airport and its strings. */
Airport* createAirport(const char* gpsId,
                       const char* type,
                       const char* name,
                       double latitude,
                       double longitude,
                       int elevationFeet,
                       const char* city,
                       const char* countryAbbrv);

/* Initialize an existing Airport structure (deep copies strings).
 * If `airport` is NULL the function does nothing. */
void initAirport(Airport* airport,
                 const char* gpsId,
                 const char* type,
                 const char* name,
                 double latitude,
                 double longitude,
                 int elevationFeet,
                 const char* city,
                 const char* countryAbbrv);

/* Constructs a newly allocated string representation of `a`.
 * The caller must free() the returned string. Returns NULL on
 * NULL input or allocation failure. */
char* airportToString(const Airport* a);

/* Computes the air distance in kilometers between two airports
 * using the spherical law of cosines. Returns 0.0 on NULL input.
 */
double getAirDistance(const Airport* origin, const Airport* destination);

/* Computes estimated travel time (hours) for `size` stops (array)
 * using `aveKmsPerHour` and `aveLayoverTimeHrs` for each intermediate
 * stop. Returns 0.0 on invalid input (size < 1 or NULL stops). */
double getEstimatedTravelTime(const Airport* stops,
                              int size,
                              double aveKmsPerHour,
                              double aveLayoverTimeHrs);

/* Free an Airport and its allocated members. Safe to pass NULL. */
void freeAirport(Airport* a);

#endif /* HACK11_AIRPORT_H */
