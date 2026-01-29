
#include "../earthquake.h"

/**
 * string structure used to keep track of the size
 * of the allocated space.  Used by the curl library
 * as a buffer.
 */
struct string {
  char *ptr;
  size_t len;
};

/**
 * Initializes a string structure
 */
void initString(struct string *s);

/**
 * Callback used by the curl function so that we capture the curl
 * stream to a buffer.  This function automatically expands the
 * buffer via realloc (exiting on failure).
 */
size_t bufferedWrite(void *ptr, size_t size, size_t nmemb, struct string *s);

/**
 * Function returns a string containing the content of the given
 * url.
 */
char *getContent(const char *url);

/**
 * Loads earthquake data from the given <code>url</code> and returns
 * an array of size <code>n</code>.  Data is assumed to be in the USGS
 * GeoJSON Summary format (see
 * <a href="https://earthquake.usgs.gov/earthquakes/feed/v1.0/geojson.php">here</a>
 * for details).
 *
 */
EarthquakeData *loadEarthquakeData(const char *url, int *n);

/**
 * Parses earthquake data from the given JSON string and returns
 * an array of size <code>n</code>.  Data is assumed to be in the USGS
 * GeoJSON Summary format (see
 * <a href="https://earthquake.usgs.gov/earthquakes/feed/v1.0/geojson.php">here</a>
 * for details).
 */
EarthquakeData *parseEarthquakeData(const char *json_data, int *n);
