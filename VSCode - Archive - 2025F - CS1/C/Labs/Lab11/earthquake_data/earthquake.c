/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 2025-11-11
 * Lab/Task: Lab11 - Earthquake Data
 */

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <string.h>
#include <time.h>

#include "earthquake.h"

int initEarthquakeData(EarthquakeData *data,
  const char *id,
  const char *locationName,
  double magnitude,
  int significance,
  long timestamp,
  double latitude,
  double longitude,
  double depth) {

        if (data == NULL) return 0;

        data->id = strCopy(id ? id : "");
        data->locationName = strCopy(locationName ? locationName : "");
        data->magnitude = magnitude;
        data->significance = significance;
        data->timestamp = timestamp;
        data->latitude = latitude;
        data->longitude = longitude;
        data->depth = depth;

        return 1;
}

EarthquakeData * createEarthquakeData(
  const char *id,
  const char *locationName,
  double magnitude,
  int significance,
  long timestamp,
  double latitude,
  double longitude,
  double depth) {
    EarthquakeData *data = (EarthquakeData *) malloc(sizeof(EarthquakeData));
    if (data == NULL) return NULL;
    if (!initEarthquakeData(data, id, locationName, magnitude, significance, timestamp, latitude, longitude, depth)) {
        free(data);
        return NULL;
    }
    return data;
}

char *earthquakeDataToString(const EarthquakeData *data) {

    /* convert timestamp (ms) to seconds and format as UTC */
    time_t timestamp_s = data->timestamp / 1000;
    struct tm *timeinfo = gmtime(&timestamp_s);
    char time_str[30];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S UTC", timeinfo);

     char buffer[512];
     /* Format fields: magnitude (1 decimal), significance (3-wide), time string,
        latitude/longitude (2 decimals), depth (2 decimals, km). */
     snprintf(buffer, sizeof(buffer), "%-15s %-39s %4.1f (%3d) %24s   (%7.2f, %7.2f) %6.2fkm",
                 data->id ? data->id : "",
                 data->locationName ? data->locationName : "",
                 data->magnitude,
                 data->significance,
                 time_str,
                 data->latitude,
                 data->longitude,
                 data->depth);

    char *result = malloc(strlen(buffer) + 1);
    strcpy(result, buffer);
    return result;
}


void earthquakeDataPrint(const EarthquakeData *data) {
    char *str = earthquakeDataToString(data);
    printf("%s\n", str);
    free(str);
    return;
}

void earthquakeDataPrintAll(const EarthquakeData *data, int n) {
    printf("Earthquake Data (n = %d)\n", n);
    printf("%-15s %-39s %s %24s %20s %8s\n", "Id",
                                  "Location",
                                  "magnitude/(sig)",
                                  "time",
                                  "lat/lon", "depth");
    for(int i=0; i<n; i++) {
        earthquakeDataPrint(&data[i]);
    }
    printf("\n\n");
}


char *strCopy(const char *str) {
    char *copy = (char *) malloc(sizeof(char) * (strlen(str)+1));
    strcpy(copy, str);
    return copy;
}

void runReports(const EarthquakeData *data, int n) {

    /* find minimum magnitude earthquake */
    int minMagnitudeIndex = 0;
    for(int i=1; i<n; i++) {
        if(data[i].magnitude < data[minMagnitudeIndex].magnitude) {
            minMagnitudeIndex = i;
        }
    }
    printf("Weakest Magnitude Earthquake: \n");
    earthquakeDataPrint(&data[minMagnitudeIndex]);

    /* find maximum magnitude earthquake (use pointer) */
    const EarthquakeData *maxMagnitudeEarthquake = &data[0];
    for(int i=1; i<n; i++) {
        if(data[i].magnitude > maxMagnitudeEarthquake->magnitude) {
            maxMagnitudeEarthquake = &data[i];
        }
    }
    printf("Strongest Magnitude Earthquake: \n");
    earthquakeDataPrint(maxMagnitudeEarthquake);

    /* find the closest earthquake to Lincoln, NE (40.806862, -96.681679) */
    const double lincolnLat = 40.806862;
    const double lincolnLon = -96.681679;
    int closestIndex = -1;
    double minDistance = -1.0;
    for (int i = 0; i < n; i++) {
        double d = airDistance(lincolnLat, lincolnLon, data[i].latitude, data[i].longitude);
        if (minDistance < 0 || d < minDistance) {
            minDistance = d;
            closestIndex = i;
        }
    }
    if (closestIndex >= 0) {
        printf("Closest Earthquake to Lincoln (%.2f kms away): \n", minDistance);
        earthquakeDataPrint(&data[closestIndex]);
    } else {
        printf("Closest Earthquake to Lincoln: (no data)\n");
    }

    return;
}

double airDistance(double originLatitude,
         double originLongitude,
         double destinationLatitude,
         double destinationLongitude) {

  originLatitude = originLatitude * M_PI / 180;
  originLongitude = originLongitude * M_PI / 180;
  destinationLatitude = destinationLatitude * M_PI / 180;
  destinationLongitude = destinationLongitude * M_PI / 180;

  double distance = acos(sin(originLatitude) * sin(destinationLatitude) + cos(originLatitude) * cos(destinationLatitude) * cos(destinationLongitude-originLongitude)) * 6371.0;
  return distance;
}
