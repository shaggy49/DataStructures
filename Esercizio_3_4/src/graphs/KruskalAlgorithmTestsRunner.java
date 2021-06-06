package graphs;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class KruskalAlgorithmTestsRunner {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Result result = JUnitCore.runClasses(KruskalAlgorithmTests.class);
        for (Failure failure : result.getFailures()) {
            System.err.println(failure.toString());
        }
        System.out.println("Undirected Graph (String nodes, Float Edges): " + result.wasSuccessful());
    }
}
