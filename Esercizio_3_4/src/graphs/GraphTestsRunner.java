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

// java -jar GraphTestsRunner.jar

/*
public class GraphTests {
	public static void main(String[] args) {
		Graph<String, String> gr = new Graph<>("directed");
		List<Edge<String, String>> l= new LinkedList<>();

		try{
			//gr.addUndirectedEdge("A", "B", 30);
			//gr.addUndirectedEdge("B", "A", 30);
			gr.addNode("A");
			gr.addEdge("A", "C", "20");
			gr.addEdge("A", "C", "22");
			gr.addEdge("A", "E", "20");
			gr.addEdge("A", "D", "255");
			gr.addEdge("A", "P", "ciaone");
			gr.addEdge("X", "A", "evviva");
			gr.addEdge("P", "X", "ritorno");
			System.out.println("Grafo iniziale appena creato:");
			System.out.println(gr);
			System.out.println("Il grafo contiene " + gr.getNumberOfNodes() + " nodi e " + gr.getNumberOfEdges() + " archi");
			System.out.println("Gli adiacenti del nodo A sono:");
			System.out.println(gr.getAdiacentsFromNode("A"));
			System.out.println("Il grafo contiene l'arco (A ==> P : ciaone):");
			System.out.println(gr.containsEdge("A", "P", "ciaone"));
			System.out.println("Rimozione dell'arco (A ==> E : 20):");
			gr.removeEdge("A", "E", "20");
			System.out.println(gr);
			System.out.println("Rimozione del nodo A:");
			gr.removeNode("A");
			System.out.println(gr);
			System.out.println("Il grafo contiene " + gr.getNumberOfNodes() + " nodi e " + gr.getNumberOfEdges() + " archi");
			System.out.println("Recupero etichetta da due nodi di un arco (X,D):");
			System.out.println(gr.getEdgeWeight("X", "D"));
			System.out.println("Recupero archi del nodo C:");
			l = gr.getEdgesFromNode("C");
			System.out.println(l);
			System.out.println("Recupero nodi di tutto il grafo:");
			System.out.println(gr.graphNodes());
			System.out.println("Recupero archi di tutto il grafo:");
			System.out.println(gr.graphEdges());
			if (gr.isDirected())
				System.out.println("Il grafo è orientato");
			else
				System.out.println("Il grafo è non orientato");
		}
		catch(Exception ex){
			System.err.println(ex.getMessage());
		}
	}
}
*/
