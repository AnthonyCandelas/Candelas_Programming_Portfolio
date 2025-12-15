package unl.soc;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 08Dec2025
 * Lab/Task: Hack13 - Airport sorting and searching (Java)
 *
 * Description:
 * Utilities for sorting/searching Airport records and generating
 * report output matching the Hack13 specification.
 */
public class AirportUtils {

    private static final double LINCOLN_LAT = 40.846176;
    private static final double LINCOLN_LON = -96.75471;

	/**
	 * A comparator function that orders the two Airport structures by their GPS IDs
	 * in lexicographic order.
	 */
	public static final Comparator<Airport> CMP_GPS_ID = new Comparator<>() {
		@Override
		public int compare(Airport a1, Airport a2) {
			return a1.getGpsId().compareTo(a2.getGpsId());
		}
	};

	/**
	 * A comparator function that orders the two Airport structures by their type.
	 */
	public static final Comparator<Airport> CMP_TYPE = new Comparator<>() {
		@Override
		public int compare(Airport a1, Airport a2) {
			return a1.getType().compareTo(a2.getType());
		}
	};

	/**
	 * A comparator function that orders the two Airport structures by their name in
	 * lexicographic order.
	 */
	public static final Comparator<Airport> CMP_NAME = new Comparator<>() {
		@Override
		public int compare(Airport a1, Airport a2) {
			return a1.getName().compareTo(a2.getName());
		}
	};

	/**
	 * A comparator function that orders the two Airport structures by their name in
	 * reverse lexicographic order.
	 */
	public static final Comparator<Airport> CMP_NAME_DESC = new Comparator<>() {
		@Override
		public int compare(Airport a1, Airport a2) {
			return a2.getName().compareTo(a1.getName());
		}
	};

	/**
	 * A comparator function that orders the two Airport structures first by
	 * country, then by city
	 */
	public static final Comparator<Airport> CMP_COUNTRY_CITY = new Comparator<>() {
		@Override
		public int compare(Airport a1, Airport a2) {
			int country = a1.getCountryAbbrv().compareTo(a2.getCountryAbbrv());
			if (country != 0) {
				return country;
			}
			return a1.getCity().compareTo(a2.getCity());
		}
	};

	/**
	 * A comparator function that orders the given Airport structures by their
	 * latitudes north to south
	 */
	public static final Comparator<Airport> CMP_LATITUDE = new Comparator<>() {
		@Override
		public int compare(Airport a1, Airport a2) {
			return Double.compare(a2.getLatitude(), a1.getLatitude());
		}
	};

	/**
	 * A comparator function that orders the given Airport structures by their
	 * longitudes west to east
	 */
	public static final Comparator<Airport> CMP_LONGITUDE = new Comparator<>() {
		@Override
		public int compare(Airport a1, Airport a2) {
			return Double.compare(a1.getLongitude(), a2.getLongitude());
		}
	};

	/**
	 * A comparator function that orders the two Airport structures by their
	 * relative distance from Lincoln Municipal Airport (0R2, 40.846176, -96.75471)
	 * in ascending order according (closest to Lincoln would come first)
	 */
	public static final Comparator<Airport> CMP_LINCOLN_DISTANCE = new Comparator<>() {
		@Override
		public int compare(Airport a1, Airport a2) {
			Airport lincoln = new Airport("LIN", "Lincoln", LINCOLN_LAT, LINCOLN_LON, "ref", 0, "Lincoln",
					"US");
			double d1 = lincoln.getAirDistance(a1);
			double d2 = lincoln.getAirDistance(a2);
			return Double.compare(d1, d2);
		}
	};

	/**
	 * A function that generates and prints several reports on the given list of
	 * Airports.
	 */
	public static void generateReports(List<Airport> airports) {
		if (airports == null || airports.isEmpty()) {
			return;
		}

		printHeader("Airports (original):");
		printAirports(airports);

		printSortedReport("Airports By GPS ID:", airports, CMP_GPS_ID);
		printSortedReport("Airports By Type:", airports, CMP_TYPE);
		printSortedReport("Airports By Name:", airports, CMP_NAME);
		printSortedReport("Airports By Name - Reversed:", airports, CMP_NAME_DESC);
		printSortedReport("Airports By Country/City:", airports, CMP_COUNTRY_CITY);
		printSortedReport("Airports By Latitude:", airports, CMP_LATITUDE);
		printSortedReport("Airports By Longitude:", airports, CMP_LONGITUDE);
		printSortedReport("Airports By Distance from Lincoln:", airports, CMP_LINCOLN_DISTANCE);

		List<Airport> distSorted = new ArrayList<>(airports);
		Collections.sort(distSorted, CMP_LINCOLN_DISTANCE);
		printHeader("Closest Airport to Lincoln:");
		System.out.println(distSorted.get(0));
		printHeader("Furthest Airport from Lincoln:");
		System.out.println(distSorted.get(distSorted.size() - 1));

		List<Airport> lonSorted = new ArrayList<>(airports);
		Collections.sort(lonSorted, CMP_LONGITUDE);
		int medianIndex = lonSorted.size() / 2;
		printHeader("East-West Geographic Center:");
		System.out.println(lonSorted.get(medianIndex));

		printHeader("New York, NY airport:");
		Airport ny = findFirst(airports, a -> a.getCity().equals("New York") && a.getCountryAbbrv().equals("US"));
		if (ny != null) {
			System.out.println(ny);
		} else {
			System.out.println("No New York airport found!");
		}

		printHeader("Large airport:");
		Airport large = findFirst(airports, a -> a.getType().equals("large_airport"));
		if (large != null) {
			System.out.println(large);
		} else {
			System.out.println("No large airport found!");
		}
	}

	private static void printHeader(String title) {
		System.out.printf("\n%s \n", title);
		System.out.printf("==============================\n");
	}

	private static void printAirports(List<Airport> airports) {
		for (Airport a : airports) {
			System.out.println(a);
		}
	}

	private static void printSortedReport(String title, List<Airport> airports, Comparator<Airport> cmp) {
		List<Airport> copy = new ArrayList<>(airports);
		Collections.sort(copy, cmp);
		printHeader(title);
		printAirports(copy);
	}

	private interface AirportPredicate {
		boolean test(Airport a);
	}

	private static Airport findFirst(List<Airport> airports, AirportPredicate predicate) {
		for (Airport a : airports) {
			if (predicate.test(a)) {
				return a;
			}
		}
		return null;
	}

	public static void main(String[] args) {
		List<Airport> airports = new ArrayList<>();
		airports.add(new Airport("OMA", "Eppley Airfield", 41.3030, -95.8940, "normal", 150, "Omaha", "US"));
		airports.add(new Airport("ORD", "O'Hare", 41.9742, -87.9073, "huge", 125, "Chicago", "US"));
		airports.add(new Airport("YYZ", "Pearson", 43.60, -79.60, "large_airport", 25, "Toronto", "CN"));
		airports.add(new Airport("LGA", "LaGuardia", 40.7769, -73.8740, "international", 50, "New York", "US"));
		airports.add(new Airport("SYD", "Sydney Airport", -33.9461, 151.1772, "large_airport", 21, "Sydney", "AU"));
		airports.add(new Airport("LHR", "Heathrow", 51.4700, -0.4543, "large_airport", 83, "London", "GB"));

		generateReports(airports);
	}

}
