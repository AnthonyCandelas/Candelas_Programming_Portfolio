package Java.Hack11;

/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 18NOV2025
 * Lab/Task: Hack11 - Airport Tester (Java)
 *
 * Description:
 * Simple tester harness for the Java Airport class used in Hack11.
 * It demonstrates building a small list of airports and calling
 * distance/time utilities.
 */

import unl.soc.Airport;
import java.util.Arrays;
import java.util.List;

public class AirportTester {
	public static void main(String[] args) {
		Airport jfk = new Airport("KJFK", "John F Kennedy Intl", 40.6413, -73.7781, "large_airport", 13, "New York", "US");
		Airport lax = new Airport("KLAX", "Los Angeles Intl", 33.9416, -118.4085, "large_airport", 125, "Los Angeles", "US");
		Airport ord = new Airport("KORD", "Chicago O'Hare Intl", 41.9742, -87.9073, "large_airport", 672, "Chicago", "US");
		List<Airport> stops = Arrays.asList(jfk, ord, lax);
		System.out.printf("Distance JFK-LAX: %.2f km\n", jfk.getAirDistance(lax));
		System.out.printf("Estimated travel time (JFK -> ORD -> LAX) at 900 km/h, 1h layover: %.2f hours\n",
				Airport.getEstimatedTravelTime(stops, 900.0, 1.0));
	}
}
