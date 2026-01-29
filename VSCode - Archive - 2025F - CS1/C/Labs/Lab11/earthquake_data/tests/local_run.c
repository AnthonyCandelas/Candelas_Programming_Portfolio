#include <stdio.h>
#include <stdlib.h>
#include "../earthquake.h"

int main(void) {
    EarthquakeData data[4];

    initEarthquakeData(&data[0], "eq1", "Near Lincoln, NE", 2.5, 10, 1751485191000L, 40.806862, -96.681679, 5.0);
    initEarthquakeData(&data[1], "eq2", "Far away", 4.0, 50, 1751485192000L, 35.0, -118.3, 3.4);
    initEarthquakeData(&data[2], "eq3", "Nearby town", 1.2, 5, 1751485193000L, 40.0, -96.0, 2.0);
    initEarthquakeData(&data[3], "eq4", "Another", 3.1, 20, 1751485194000L, 59.95, -149.44, 27.0);

    earthquakeDataPrintAll(data, 4);
    runReports(data, 4);

    /* free allocated strings */
    for (int i = 0; i < 4; i++) {
        free(data[i].id);
        free(data[i].locationName);
    }

    return 0;
}
