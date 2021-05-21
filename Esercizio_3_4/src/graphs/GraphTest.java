// package graphs

import java.util.*;

public class GraphTest {
	public static void main(String[] args) {
		Graph<String, String> gr = new Graph<>();
		List<Edge<String, String>> l= new LinkedList<>();
		boolean b = false;

		try{
			/* gr.addUndirectedEdge("A", "B", 30);
			gr.addUndirectedEdge("B", "A", 30); */
			gr.addNode("A");
			gr.addDirectedEdge("A", "C", "20");
			gr.addDirectedEdge("A", "E", "20");
			gr.addDirectedEdge("A", "D", "20");
			gr.addDirectedEdge("A", "P", "20");
			System.out.println(gr);
			b = gr.containsEdge("A", "C", "20");
			System.out.println(b);
			gr.removeEdge("A", "E", "20");
			System.out.println(gr);
			l = gr.getEdgesFromNode("C");
			System.out.println("Recupero archi e nodi grafo:");
			gr.graphEdges();
			gr.graphNodes();
		}
		catch(GraphException ex){
			System.err.println(ex.getMessage());
		}
		if (gr.isDirected())
			System.out.println("Diretto");
		else
			System.out.println("Indiretto");
	}
}
