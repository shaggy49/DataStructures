// package graphs

import java.util.*;

public class GraphTest {
	public static void main(String[] args) {
		Graph<String, Integer> gr = new Graph<>();
		List<Edge<String, Integer>> l= new LinkedList<>();
		boolean b = false;

		try{
			/* gr.addUndirectedEdge("A", "B", 30);
			gr.addUndirectedEdge("B", "A", 30); */
			gr.addDirectedEdge("A", "C", 20);
			gr.addDirectedEdge("A", "4", 20);
			gr.addDirectedEdge("A", "7", 20);
			gr.addDirectedEdge("C", "A", 30);
			gr.addDirectedEdge("C", "B", 80);
			gr.addDirectedEdge("3", "c", 20);
			b = gr.containsEdge("A", "4", 20);
			l = gr.getEdgesFromNode("C");
			//gr.removeNode("F"); //non sono sicuro pero` di come sia implementatoS
			
		}
		catch(GraphException ex){
			System.err.println(ex.getMessage());
		}
		if (gr.isDirected())
			System.out.println("Diretto");
		else
			System.out.println("Indiretto");

		//System.out.println(l);			//se l è vuota --> stampa "[]"
		//System.out.println(b);
		//System.out.println(gr);
		gr.graphNodes();
		gr.graphEdges();
	}
}
