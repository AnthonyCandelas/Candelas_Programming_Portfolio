/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Exam 2 - Flood Utilities
 *
 * Description:
 * Utilities for Exam 2 to convert flow measurements and compute flood
 * capacity for a grid of elevations. Behavior for null and empty inputs is
 * documented in the header and in each method's Javadoc.
 */

package unl.soc;

import java.util.List;
import java.util.ArrayList;

/**
 * CSCE 155H - Fall 2025 Exam 2
 */
public class FloodUtils {

	/**
	 * Converts a list of area measurements from square meters to square feet.
	 *
	 * @param flow List of area values in square meters. Must be non-null.
	 *        Elements must be non-null Doubles.
	 * @return A new List<Double> where each value is converted to square
	 *         feet. Returns an empty list when the input list is empty.
	 * @throws NullPointerException if {@code flow} is null or any element is null
	 */
	public static List<Double> convertFlow(List<Double> flow) {
		if (flow == null) {
			throw new NullPointerException("flow list must not be null");
		}

		List<Double> out = new ArrayList<>(flow.size());
		final double SQM_TO_SQFT = 10.76391;

		for (Double v : flow) {
			if (v == null) {
				throw new NullPointerException("flow elements must not be null");
			}
			out.add(v * SQM_TO_SQFT);
		}

		return out;
	}

	/**
	 * Computes the total flood capacity of the given grid of elevations
	 * with respect to the given waterLevel. Capacity is the sum of
	 * (waterLevel - elevation) for every cell where elevation < waterLevel.
	 *
	 * @param elevations A 2D array representing an n-by-m grid. If null or any
	 *        row is null the function returns Double.NaN. An empty grid
	 *        (zero rows) has capacity 0.0.
	 * @param waterLevel The water level to use when computing capacity.
	 * @return The total flood capacity (same units as elevation). Returns
	 *         Double.NaN on invalid input.
	 */
	public static double floodCapacity(double elevations[][], double waterLevel) {
		if (elevations == null) {
			return Double.NaN;
		}

		if (elevations.length == 0) {
			return 0.0;
		}

		double total = 0.0;

		for (int i = 0; i < elevations.length; i++) {
			double[] row = elevations[i];
			if (row == null) {
				return Double.NaN;
			}
			for (int j = 0; j < row.length; j++) {
				double elev = row[j];
				if (elev < waterLevel) {
					total += (waterLevel - elev);
				}
			}
		}

		return total;
	}

}
