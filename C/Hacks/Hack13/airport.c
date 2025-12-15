#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "airport.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define LINCOLN_LAT 40.846176
#define LINCOLN_LON -96.75471
static char* strCopy(const char* src) {
  if (!src) return NULL;
  return strdup(src);
}
static double deg2rad(double deg) {
  return deg * M_PI / 180.0;
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

double getAirDistance(const Airport* origin, const Airport* destination) {
  if (!origin || !destination) return 0.0;
  double phi1 = deg2rad(origin->latitude);
  double phi2 = deg2rad(destination->latitude);
  double deltaLambda = deg2rad(destination->longitude - origin->longitude);
  double cosval = sin(phi1) * sin(phi2) + cos(phi1) * cos(phi2) * cos(deltaLambda);
  if (cosval > 1.0) cosval = 1.0;
  if (cosval < -1.0) cosval = -1.0;
  double central = acos(cosval);
  const double R = 6371.0;
  return central * R;
}

double getEstimatedTravelTime(const Airport* stops,
                              int size,
                              double aveKmsPerHour,
                              double aveLayoverTimeHrs) {
  if (!stops || size < 1 || aveKmsPerHour <= 0.0) return 0.0;
  if (size == 1) return 0.0;
  double totalHours = 0.0;
  for (int i = 0; i < size - 1; ++i) {
    double dist = getAirDistance(&stops[i], &stops[i+1]);
    totalHours += dist / aveKmsPerHour;
  }
  if (size > 2 && aveLayoverTimeHrs > 0.0) {
    totalHours += (size - 2) * aveLayoverTimeHrs;
  }
  return totalHours;
}
int cmpByGPSId(const void* a, const void* b) {
  const Airport* aa = (const Airport*)a;
  const Airport* bb = (const Airport*)b;
  return strcmp(aa->gpsId, bb->gpsId);
}

int cmpByType(const void* a, const void* b) {
  const Airport* aa = (const Airport*)a;
  const Airport* bb = (const Airport*)b;
  return strcmp(aa->type, bb->type);
}

int cmpByName(const void* a, const void* b) {
  const Airport* aa = (const Airport*)a;
  const Airport* bb = (const Airport*)b;
  return strcmp(aa->name, bb->name);
}

int cmpByNameDesc(const void* a, const void* b) {
  const Airport* aa = (const Airport*)a;
  const Airport* bb = (const Airport*)b;
  return strcmp(bb->name, aa->name);
}

int cmpByCountryCity(const void* a, const void* b) {
  const Airport* aa = (const Airport*)a;
  const Airport* bb = (const Airport*)b;
  int countryResult = strcmp(aa->countryAbbrv, bb->countryAbbrv);
  if (countryResult != 0) {
    return countryResult;
  }
  return strcmp(aa->city, bb->city);
}

int cmpByLatitude(const void* a, const void* b) {
  const Airport* aa = (const Airport*)a;
  const Airport* bb = (const Airport*)b;
  if (aa->latitude > bb->latitude) return -1;
  if (aa->latitude < bb->latitude) return 1;
  return 0;
}

int cmpByLongitude(const void* a, const void* b) {
  const Airport* aa = (const Airport*)a;
  const Airport* bb = (const Airport*)b;
  if (aa->longitude < bb->longitude) return -1;
  if (aa->longitude > bb->longitude) return 1;
  return 0;
}

int cmpByLincolnDistance(const void* a, const void* b) {
  const Airport* aa = (const Airport*)a;
  const Airport* bb = (const Airport*)b;
  Airport lincoln;
  lincoln.latitude = LINCOLN_LAT;
  lincoln.longitude = LINCOLN_LON;
  
  double distA = getAirDistance(&lincoln, aa);
  double distB = getAirDistance(&lincoln, bb);
  
  if (distA < distB) return -1;
  if (distA > distB) return 1;
  return 0;
}
char* airportToString(const Airport* a) {
  char temp[1000];
  sprintf(temp, "%-8s %-15s %-20s %.2f %.2f %d %-10s %-2s",
          a->gpsId, a->type, a->name,
          a->latitude, a->longitude, a->elevationFeet, a->city,
          a->countryAbbrv);
  char* result = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
  strcpy(result, temp);
  return result;
}

void printAirports(Airport *airports, int n) {
  for (int i = 0; i < n; i++) {
    char *s = airportToString(&airports[i]);
    printf("%s\n", s);
    free(s);
  }
}

void generateReports(Airport *airports, int n) {
  if (!airports || n <= 0) return;

  Airport* workingCopy = malloc(sizeof(Airport) * n);
  if (!workingCopy) return;

  printf("Airports (original): \n");
  printf("==============================\n");
  printAirports(airports, n);

  memcpy(workingCopy, airports, sizeof(Airport) * n);
  qsort(workingCopy, n, sizeof(Airport), cmpByGPSId);
  printf("\nAirports By GPS ID: \n");
  printf("==============================\n");
  printAirports(workingCopy, n);

  memcpy(workingCopy, airports, sizeof(Airport) * n);
  qsort(workingCopy, n, sizeof(Airport), cmpByType);
  printf("\nAirports By Type: \n");
  printf("==============================\n");
  printAirports(workingCopy, n);

  memcpy(workingCopy, airports, sizeof(Airport) * n);
  qsort(workingCopy, n, sizeof(Airport), cmpByName);
  printf("\nAirports By Name: \n");
  printf("==============================\n");
  printAirports(workingCopy, n);

  memcpy(workingCopy, airports, sizeof(Airport) * n);
  qsort(workingCopy, n, sizeof(Airport), cmpByNameDesc);
  printf("\nAirports By Name - Reversed: \n");
  printf("==============================\n");
  printAirports(workingCopy, n);

  memcpy(workingCopy, airports, sizeof(Airport) * n);
  qsort(workingCopy, n, sizeof(Airport), cmpByCountryCity);
  printf("\nAirports By Country/City: \n");
  printf("==============================\n");
  printAirports(workingCopy, n);

  memcpy(workingCopy, airports, sizeof(Airport) * n);
  qsort(workingCopy, n, sizeof(Airport), cmpByLatitude);
  printf("\nAirports By Latitude: \n");
  printf("==============================\n");
  printAirports(workingCopy, n);

  memcpy(workingCopy, airports, sizeof(Airport) * n);
  qsort(workingCopy, n, sizeof(Airport), cmpByLongitude);
  printf("\nAirports By Longitude: \n");
  printf("==============================\n");
  printAirports(workingCopy, n);

  memcpy(workingCopy, airports, sizeof(Airport) * n);
  qsort(workingCopy, n, sizeof(Airport), cmpByLincolnDistance);
  printf("\nAirports By Distance from Lincoln: \n");
  printf("==============================\n");
  printAirports(workingCopy, n);

  printf("\nClosest Airport to Lincoln: \n");
  printf("==============================\n");
  char *s = airportToString(&workingCopy[0]);
  printf("%s\n", s);
  free(s);

  printf("\nFurthest Airport from Lincoln: \n");
  printf("==============================\n");
  s = airportToString(&workingCopy[n-1]);
  printf("%s\n", s);
  free(s);

  memcpy(workingCopy, airports, sizeof(Airport) * n);
  qsort(workingCopy, n, sizeof(Airport), cmpByLongitude);
  int medianIndex = n / 2;
  printf("\nEast-West Geographic Center: \n");
  printf("==============================\n");
  s = airportToString(&workingCopy[medianIndex]);
  printf("%s\n", s);
  free(s);

  printf("\nNew York, NY airport: \n");
  printf("==============================\n");
  int foundNY = 0;
  for (int i = 0; i < n; i++) {
    if (strcmp(airports[i].city, "New York") == 0 && 
        strcmp(airports[i].countryAbbrv, "US") == 0) {
      s = airportToString(&airports[i]);
      printf("%s\n", s);
      free(s);
      foundNY = 1;
      break;
    }
  }
  if (!foundNY) {
    printf("No New York airport found!\n");
  }

  printf("\nLarge airport: \n");
  printf("==============================\n");
  int foundLarge = 0;
  for (int i = 0; i < n; i++) {
    if (strcmp(airports[i].type, "large_airport") == 0) {
      s = airportToString(&airports[i]);
      printf("%s\n", s);
      free(s);
      foundLarge = 1;
      break;
    }
  }
  if (!foundLarge) {
    printf("No large airport found!\n");
  }

  free(workingCopy);
  return;
}
