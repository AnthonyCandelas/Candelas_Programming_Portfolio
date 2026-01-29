#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "earthquake.h"
#include "data/local_data.h"
#include "utils/utils.h"

const char *usgs_earthquake_url_hour = "https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/all_hour.geojson";
const char *usgs_earthquake_url_day  = "https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/all_day.geojson";
const char *usgs_earthquake_url_week = "https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/all_week.geojson";

int main(int argc, char **argv) {

    int n;
    EarthquakeData *data = NULL;
    if(argc == 1) {
        data = loadEarthquakeData(usgs_earthquake_url_week, &n);
    } else if(argc == 2) {
        if( strcmp(argv[1], "hour") == 0 ) {
            data = loadEarthquakeData(usgs_earthquake_url_hour, &n);
        } else if( strcmp(argv[1], "day") == 0 ) {
            data = loadEarthquakeData(usgs_earthquake_url_day, &n);
        } else if( strcmp(argv[1], "week") == 0 ) {
            data = loadEarthquakeData(usgs_earthquake_url_week, &n);
        } else if( strcmp(argv[1], "local") == 0 ) {
            data = parseEarthquakeData(LOCAL_DATA_JSON, &n);
        }
    }

    if(data == NULL) {
        fprintf(stderr, "Usage: %s [hour|day|week(default)|local]\n", argv[0]);
        exit(1);
    }

    earthquakeDataPrintAll(data, n);

    runReports(data, n);

    return 0;
}
