package unl.soc;

public class TestFloodCapacity {
    public static void main(String[] args) {
        double[][] empty = new double[0][];
        double cap = FloodUtils.floodCapacity(empty, 10.0);
        System.out.println("floodCapacity(empty,10.0) = " + cap);

        double[][] grid = {
            {5.0, 5.0, 5.0},
            {5.0, 4.5, 5.0},
            {6.0, 5.5, 7.0}
        };
        System.out.println("floodCapacity(example,7.0) = " + FloodUtils.floodCapacity(grid, 7.0));
    }
}
