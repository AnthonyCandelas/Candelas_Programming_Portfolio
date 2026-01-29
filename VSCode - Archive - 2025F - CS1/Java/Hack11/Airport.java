package unl.soc;

/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 18NOV2025
 * Lab/Task: Hack11 - Airport (Java)
 *
 * Description:
 * Java model class for an Airport used in Hack11. This class stores
 * basic airport metadata (GPS id, name, coordinates, type, elevation,
 * city, country) and provides distance/time utility methods.
 *
 * NOTE: Implementations should avoid storing mutable shared state that
 * would require external synchronization.
 */

import java.util.List;

public class Airport {

	// Member variables (TODO: adjust visibility as needed)
	private final String gpsId;
	private final String name;
	private final double latitude;
	private final double longitude;
	private final String type;
	private final int elevationFeet;
	private final String city;
	private final String country;

	/**
	 * Required constructor
	 */
	public Airport(String gpsId, String name, double latitude, double longitude, String type, int elevationFeet,
			String city, String country) {
		this.gpsId = gpsId;
		this.name = name;
		this.latitude = latitude;
		this.longitude = longitude;
		this.type = type;
		this.elevationFeet = elevationFeet;
		this.city = city;
		this.country = country;
	}

	/**
	 * Computes the air distance, in kilometers, from this airport to the given
	 * destination using Spherical Law of Cosines.
	 */
	public double getAirDistance(Airport destination) {
		final double R = 6371.0; // Earth's radius in km
		double lat1 = Math.toRadians(this.latitude);
		double lon1 = Math.toRadians(this.longitude);
		double lat2 = Math.toRadians(destination.latitude);
		double lon2 = Math.toRadians(destination.longitude);
		double central = Math.acos(Math.sin(lat1) * Math.sin(lat2)
				+ Math.cos(lat1) * Math.cos(lat2) * Math.cos(lon1 - lon2));
		return R * central;
	}

	/**
	 * Computes the estimated travel time (in hours) for a flight that involves the
	 * given stops using the average flight speed (kilometers per hour) and average
	 * layover time (in hours)
	 */
	public static double getEstimatedTravelTime(List<Airport> stops, double aveKmsPerHour, double aveLayoverTimeHrs) {
		if (stops == null || stops.size() < 2) return 0.0;
		double totalKm = 0.0;
		for (int i = 0; i < stops.size() - 1; i++) {
			totalKm += stops.get(i).getAirDistance(stops.get(i + 1));
		}
		double flightHours = totalKm / aveKmsPerHour;
		double layovers = Math.max(0, stops.size() - 2);
		return flightHours + (layovers * aveLayoverTimeHrs);
	}

	// Getters (optional)
	public String getGpsId() { return gpsId; }
	public String getName() { return name; }
	public double getLatitude() { return latitude; }
	public double getLongitude() { return longitude; }
}

}