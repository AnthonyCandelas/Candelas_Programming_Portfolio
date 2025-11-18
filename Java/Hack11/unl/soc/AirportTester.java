/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 17Nov2025
 * Lab/Task: Hack11 - Airport tester (Java)
 */
package unl.soc;

public class AirportTester {
    private static void header(String s) {
        System.out.println();
        System.out.println("=== " + s + " ===");
    }

    public static void main(String[] args) {
        header("createAirport tests");
        Airport jfk = new Airport("KJFK", "John F. Kennedy International Airport", 40.6413, -73.7781,
                      "large_airport", 13, "Queens", "US");
        Airport lax = new Airport("KLAX", "Los Angeles International Airport", 33.9416, -118.4085,
                      "large_airport", 125, "Los Angeles", "US");
        Airport ord = new Airport("KORD", "O'Hare International Airport", 41.9742, -87.9073,
                      "large_airport", 672, "Chicago", "US");

        System.out.println("[case 1] " + jfk.toString());
        System.out.println("[case 2] " + lax.toString());
        System.out.println("[case 3] " + ord.toString());

        header("getAirDistance tests");
        double d1 = jfk.getAirDistance(lax);
        double d2 = lax.getAirDistance(jfk);
        double d3 = jfk.getAirDistance(jfk);
        System.out.printf("[case 1] JFK -> LAX = %.2f km\n", d1);
        System.out.printf("[case 2] LAX -> JFK = %.2f km\n", d2);
        System.out.printf("[case 3] JFK -> JFK = %.2f km\n", d3);

        header("getEstimatedTravelTime tests");
        java.util.List<Airport> direct = java.util.Arrays.asList(jfk, lax);
        double t_direct = Airport.getEstimatedTravelTime(direct, 900.0, 1.0);
        System.out.printf("[case 1] JFK -> LAX @900km/h = %.2f hours\n", t_direct);

        java.util.List<Airport> multi = java.util.Arrays.asList(jfk, ord, lax);
        double t_multi = Airport.getEstimatedTravelTime(multi, 900.0, 1.0);
        System.out.printf("[case 2] JFK -> ORD -> LAX @900km/h, 1hr layover = %.2f hours\n", t_multi);

        java.util.List<Airport> single = java.util.Arrays.asList(jfk);
        double t_single = Airport.getEstimatedTravelTime(single, 900.0, 1.0);
        System.out.printf("[case 3] single stop = %.2f hours\n", t_single);
    }
}
