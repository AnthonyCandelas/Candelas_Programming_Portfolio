#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <json.h>

#include "utils.h"

void initString(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len + 1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t bufferedWrite(void *ptr, size_t size, size_t nmemb, struct string *s) {
  size_t new_len = s->len + size * nmemb;
  s->ptr = realloc(s->ptr, new_len + 1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr + s->len, ptr, size * nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size * nmemb;
}

char *getContent(const char *url) {
  char *result = NULL;
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    struct string s;
    initString(&s);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "F your user agent tracking BS");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, bufferedWrite);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprintf(stderr, "cURL encountered an error: %s\n", curl_easy_strerror(res));
    }

    result = (char *)malloc(sizeof(char) * (strlen(s.ptr) + 1));
    strcpy(result, s.ptr);
    free(s.ptr);

    curl_easy_cleanup(curl);
  }
  return result;
}

EarthquakeData *parseEarthquakeData(const char *json_data, int *n) {

    struct json_object *data;
	data = json_tokener_parse(json_data);

    struct json_object *metadata = json_object_object_get(data, "metadata");
    struct json_object *count = json_object_object_get(metadata, "count");
    long numDataPoints = json_object_get_int64(count);
    *n = numDataPoints;

    EarthquakeData* result = (EarthquakeData*)malloc(numDataPoints * sizeof(EarthquakeData));

    struct json_object *features_obj = json_object_object_get(data, "features");
    //struct array_list *features = json_object_get_array(features_obj);
    int length = json_object_array_length(features_obj);
    for(int i=0; i<length; i++) {
        struct json_object *feature = json_object_array_get_idx(features_obj, i);
        //features[i].id
        const char *id = json_object_get_string(json_object_object_get(feature, "id"));
        //features[i].properties
        struct json_object *properties = json_object_object_get(feature, "properties");

        struct json_object *place = json_object_object_get(properties, "place");
        const char *locationName = json_object_get_string(place);
        double magnitude = json_object_get_double(json_object_object_get(properties, "mag"));
        int significance = json_object_get_int(json_object_object_get(properties, "sig"));
        long timestamp = json_object_get_int64(json_object_object_get(properties, "time"));

        //features[i].geometry.coordinates
        struct json_object *coordinates = json_object_object_get(json_object_object_get(feature, "geometry"), "coordinates");
        double latitude = json_object_get_double(json_object_array_get_idx(coordinates, 1));
        double longitude = json_object_get_double(json_object_array_get_idx(coordinates, 0));
        double depth = json_object_get_double(json_object_array_get_idx(coordinates, 2));

        initEarthquakeData(&result[i], id, locationName, magnitude, significance, timestamp, latitude, longitude, depth);
    }

    json_object_put(data);

    return result;
}

EarthquakeData *loadEarthquakeData(const char *url, int *n) {

	char *str = getContent(url);
    EarthquakeData *result = parseEarthquakeData(str, n);
    free(str);
    return result;
}
