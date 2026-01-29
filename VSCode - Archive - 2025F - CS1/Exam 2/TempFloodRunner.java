/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Exam 2 - Flood Utilities
 *
 * Description:
 * Quick runner for manual verification of `FloodUtils` behavior. Prints a
 * few sanity checks to stdout.
 */

package unl.soc;

import java.util.List;
import java.util.ArrayList;

public class TempFloodRunner {
    public static void main(String[] args) {
        System.out.println("Running quick checks for FloodUtils");
        // 1) convertFlow null -> expect NullPointerException
        try {
            FloodUtils.convertFlow(null);
            System.out.println("convertFlow(null): DID NOT THROW NPE");
        } catch (NullPointerException npe) {
            System.out.println("convertFlow(null): threw NPE as expected");
        } catch (Exception e) {
            System.out.println("convertFlow(null): threw unexpected exception: " + e);
        }

        // 2) floodCapacity empty grid -> expect 0.0
        double[][] empty = new double[0][];
        double cap = FloodUtils.floodCapacity(empty, 10.0);
        System.out.println("floodCapacity(empty,10.0) = " + cap);

        // 3) sanity: example grid from earlier (should be 3.5 in sample)
        double[][] grid = {
            {5.0, 5.0, 5.0},
            {5.0, 4.5, 5.0},
            {6.0, 5.5, 7.0}
        };
        double c2 = FloodUtils.floodCapacity(grid, 7.0);
        System.out.println("floodCapacity(example,7.0) = " + c2);

        // 4) convertFlow happy path
        List<Double> list = new ArrayList<>();
        list.add(350.0);
        List<Double> res = FloodUtils.convertFlow(list);
        System.out.println("convertFlow([350]) -> " + res.get(0));
    }
}
package unl.soc;

import java.util.List;
import java.util.ArrayList;

public class TempFloodRunner {
    public static void main(String[] args) {
        System.out.println("Running quick checks for FloodUtils");
        // 1) convertFlow null -> expect NullPointerException
        try {
            FloodUtils.convertFlow(null);
            System.out.println("convertFlow(null): DID NOT THROW NPE");
        } catch (NullPointerException npe) {
            System.out.println("convertFlow(null): threw NPE as expected");
        } catch (Exception e) {
            System.out.println("convertFlow(null): threw unexpected exception: " + e);
        }

        // 2) floodCapacity empty grid -> expect 0.0
        double[][] empty = new double[0][];
        double cap = FloodUtils.floodCapacity(empty, 10.0);
        System.out.println("floodCapacity(empty,10.0) = " + cap);

        // 3) sanity: example grid from earlier (should be 3.5 in sample)
        double[][] grid = {
            {5.0, 5.0, 5.0},
            {5.0, 4.5, 5.0},
            {6.0, 5.5, 7.0}
        };
        double c2 = FloodUtils.floodCapacity(grid, 7.0);
        System.out.println("floodCapacity(example,7.0) = " + c2);

        // 4) convertFlow happy path
        List<Double> list = new ArrayList<>();
        list.add(350.0);
        List<Double> res = FloodUtils.convertFlow(list);
        System.out.println("convertFlow([350]) -> " + res.get(0));
    }
}
