package unl.soc;

import java.util.List;
import java.util.ArrayList;

public class TestConvertFlow {
    public static void main(String[] args) {
        // Test that convertFlow throws NPE on null input
        try {
            FloodUtils.convertFlow(null);
            System.out.println("convertFlow(null): DID NOT THROW");
            System.exit(1);
        } catch (NullPointerException npe) {
            System.out.println("convertFlow(null): THREW NullPointerException");
        } catch (Exception e) {
            System.out.println("convertFlow(null): THREW unexpected: " + e);
            System.exit(1);
        }

        // Happy-path example
        List<Double> in = new ArrayList<>();
        in.add(350.0);
        List<Double> out = FloodUtils.convertFlow(in);
        System.out.printf("convertFlow([350]) -> %.10f\n", out.get(0));
    }
}
