/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 18NOV2025
 * Lab/Task: Hack11 - Airport
 *
 * Description:
 * Header file for the Airport utilities used in Hack11. This
 * header declares the opaque Airport type and functions that
 * create, initialize, stringify, and compute distances.
 *
 * NOTE: Functions that return malloc'd memory document ownership
 * in their comments; callers are responsible for freeing where
 * indicated.
 */

typedef struct Airport Airport;

/*
 * Creates a new Airport with deep-copied string fields.
 * Returns a pointer to a malloc'd Airport; caller must free it.
 */
Airport* createAirport(const char* gpsId,
                       const char* type,
                       const char* name,
                       double latitude,
                       double longitude,
                       int elevationFeet,
                       const char* city,
                       const char* countryAbbrv);

/*
 * Initializes an already-allocated Airport structure with deep
 * copies of the provided fields. Caller remains responsible for
 * managing the Airport memory (freeing when appropriate).
 */
void initAirport(Airport* airport,
                 const char* gpsId,
                 const char* type,
                 const char* name,
                 double latitude,
                 double longitude,
                 int elevationFeet,
                 const char* city,
                 const char* countryAbbrv);

/**
 * Constructs a new string representation of the given
 * Airport structure.
 */
char* airportToString(const Airport* a);

/**
 * Computes the air distance, in kilometers, between
 * the two Airports using their latitude/longitude
 */
double getAirDistance(const Airport* origin, const Airport* destination);

/**
 * Computes the estimated travel time (in hours) for a flight
 * that involves the given stops (an array of Airport structures
 * of the given size) using the average flight speed
 * (kilometers per hour).  Thus there are size - 1 "legs" of the
 * trip.
 *
 * The first stop is the origin and the last stop is the destination.
 * Each stop in between is a layover each incurring a wait time
 * of aveLayoverTimeHrs
 */
double getEstimatedTravelTime(const Airport* stops,
                              int size,
                              double aveKmsPerHour,
                              double aveLayoverTimeHrs);

/**
 * Frees an Airport that was returned from createAirport. Frees
 * internal strings and the structure itself.
 */
void freeAirport(Airport* a);

/**
 * Frees just the internal string fields of an Airport that was
 * initialized via initAirport but where the struct storage is
 * managed by the caller (for example, stack-allocated records).
 */
void freeAirportFields(Airport* a);