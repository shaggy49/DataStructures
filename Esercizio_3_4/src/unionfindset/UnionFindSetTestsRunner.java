package unionfindset;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class UnionFindSetTestsRunner {
    /**
     * @param args the command line arguments
     */

    public static void main(String[] args) {
        Result resultInteger = JUnitCore.runClasses(UnionFindSetIntegerTests.class);
        for (Failure failure : resultInteger.getFailures()) {
            System.err.println(failure.toString());
        }
        System.out.println("Integer: " + resultInteger.wasSuccessful());

        Result resultString = JUnitCore.runClasses(UnionFindSetStringTests.class);
        for (Failure failure : resultString.getFailures()) {
            System.err.println(failure.toString());
        }
        System.out.println("String: " + resultString.wasSuccessful());
    }
}

// java -jar UnionFindSetTestsRunner.jar
