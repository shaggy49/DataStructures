package graphs;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class GraphTestsRunner {
	/**
	 * @param args the command line arguments
	 */

	public static void main(String[] args) {
		Result result = JUnitCore.runClasses(GraphDirectedStringTests.class);
		for (Failure failure : result.getFailures()) {
			System.err.println(failure.toString());
		}
		System.out.println("Directed Graph (String nodes, String Edges): " + result.wasSuccessful());

		Result resultInteger = JUnitCore.runClasses(GraphUndirectedIntegerTests.class);
		for (Failure failure : resultInteger.getFailures()) {
			System.err.println(failure.toString());
		}
		System.out.println("Undirected Graph (Integer nodes, Double Edges): " + resultInteger.wasSuccessful());
	}
}
