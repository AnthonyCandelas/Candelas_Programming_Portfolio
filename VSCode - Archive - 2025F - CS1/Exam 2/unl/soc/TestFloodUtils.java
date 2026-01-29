package unl.soc;

import java.util.List;
import java.util.ArrayList;

/**
 * Minimal combined test for FloodUtils edge cases.
 * Prints a short, machine-friendly summary for easy copy/paste.
 */
public class TestFloodUtils {
    public static void main(String[] args) {
        // 1) convertFlow(null) -> should throw NPE
        boolean convertNullThrows = false;
        try {
            FloodUtils.convertFlow(null);
        } catch (NullPointerException npe) {
            convertNullThrows = true;
        }

        // 2) floodCapacity(empty) -> should be 0.0
        double[][] empty = new double[0][];
        double emptyCap = FloodUtils.floodCapacity(empty, 10.0);

        // 3) sanity checks (example data)
        double[][] grid = {
            {5.0, 5.0, 5.0},
            {5.0, 4.5, 5.0},
            {6.0, 5.5, 7.0}
        };
        double exampleCap = FloodUtils.floodCapacity(grid, 7.0);

        List<Double> l = new ArrayList<>();
        l.add(350.0);
        List<Double> conv = FloodUtils.convertFlow(l);

        // Print concise results
        System.out.println("convertFlow(null) throws NPE: " + convertNullThrows);
        System.out.println(String.format("floodCapacity(empty,10.0) = %.1f", emptyCap));
        System.out.println(String.format("floodCapacity(example,7.0) = %.2f", exampleCap));
        System.out.println(String.format("convertFlow([350]) -> %.10f", conv.get(0)));
    }
}
