/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 2025-11-11
 * Lab/Task: Lab11 - Earthquake Data
 *
 * Definition of the EarthquakeData structure used to represent a single
 * earthquake event parsed from the USGS feed (or local JSON). Fields use
 * dynamically allocated strings where appropriate; callers are responsible
 * for freeing any allocated EarthquakeData instances created by
 * `createEarthquakeData`.
 */

#ifndef EARTHQUAKE_H
#define EARTHQUAKE_H

typedef struct {
    char *id;            /* unique alphanumeric id (malloc'd) */
    char *locationName;  /* human readable location (malloc'd) */
    double magnitude;    /* Richter magnitude */
    int significance;    /* significance score 0..1000 */
    long timestamp;      /* unix epoch ms */
    double latitude;     /* -90..90 */
    double longitude;    /* -180..180 */
    double depth;        /* depth in kilometers */
} EarthquakeData;

/**
 * An initialization function to initialize an instance of
 * <code>EarthquakeData</code> with the given values.
 */
int initEarthquakeData(EarthquakeData *data,
  const char *id,
  const char *locationName,
  double magnitude,
  int significance,
  long timestamp,
  double latitude,
  double longitude,
  double depth);

/**
 * A factory function to create an instance of
 * <code>EarthquakeData</code> with the given values.
 */
EarthquakeData *createEarthquakeData(
  const char *id,
  const char *locationName,
  double magnitude,
  int significance,
  long timestamp,
  double latitude,
  double longitude,
  double depth);

/**
 * A function to construct a (human-readable) string representation
 * of the given <code>EarthquakeData</code> instance.
 */
char *earthquakeDataToString(const EarthquakeData *data);

/**
 * Prints a human-readable representation of the given
 * <code>EarthquakeData</code> instance to the standard output.
 */
void earthquakeDataPrint(const EarthquakeData *data);

/**
 * Prints human-readable representations (in table format) of the given
 * <code>EarthquakeData</code> instances to the standard output.
 */
void earthquakeDataPrintAll(const EarthquakeData *data, int n);

/**
 * Returns a (deep) copy of the given string.
 */
char *strCopy(const char *str);

/**
 * Runs all reports on the given earthquake data.
 */
void runReports(const EarthquakeData *data, int n);

/**
 * Computes the air distance between the two locations in
 * kilometers.
 */
double airDistance(double originLatitude,
         double originLongitude,
         double destinationLatitude,
         double destinationLongitude);

#endif /* EARTHQUAKE_H */
