// package graphs

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

/* Creazione di un grafo vuoto – O(1)
Aggiunta di un nodo – O(1) 							------FATTO------
Aggiunta di un arco – O(1)							------FATTO------
Verifica se il grafo è diretto – O(1)				------FATTO------
Verifica se il grafo contiene un dato nodo – O(1)	------FATTO------
Verifica se il grafo contiene un dato arco – O(1)  (*)	
Cancellazione di un nodo – O(n)						------FATTO------
Cancellazione di un arco – O(1)  (*)
Determinazione del numero di nodi – O(1)			------FATTO------
Determinazione del numero di archi – O(n)			------FATTO------
Recupero dei nodi del grafo – O(n)
Recupero degli archi del grafo – O(n)				
Recupero nodi adiacenti di un dato nodo – O(1)  (*)
Recupero etichetta associata a una coppia di nodi – O(1) (*) */

// V (vertex) tipo delle chiavi (nodi, vertici) 

public class Graph<V, E> {
	private Map<V, List<Edge<V, E>>> gr;
	private long nOfEdges = 0; // numero di archi, possono essere anche di grafi non orientati
	private long nOfUndirectedEdges = 0; // numero di archi indiretti
	private long nOfNodes = 0;

	public Graph() {
		gr = new HashMap<>();
	}

	// aggiunta di un nodo
	public boolean addNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("addNode: node parameter cannot be null");
		if (!gr.containsKey(node)) {
			gr.put(node, new LinkedList<>()); // inserisco in node una nuova lista vuota: node --> LinkedList(0)
			nOfNodes++;
			return true;
		}
		return false;
	}

	// agiunta di un arco
	public void addEdges(V node1, V node2, E edgeWeight) throws GraphException {
		if (!gr.containsKey(node1))
			addNode(node1);
		if (!gr.containsKey(node2))
			addNode(node2);
		/*
			* node1 (nodo partenza) node2 (nodo arrivo) edgeWeight (etichetta arco)
			*/
		gr.get(node1).add(new Edge<>(node1, node2, edgeWeight)); // inserisco nell'indice node1 una nuova chiave v1
		nOfEdges++;
	}
	// aggiunta di un arco in un grafo orientato
	public void addDirectedEdge(V node1, V node2, E edgeWeight) throws GraphException {
		if (node1 == null || node2 == null || edgeWeight == null)
			throw new GraphException("addDirectedEdge: parameter cannot be null");
		if (!(isDirected()) && nOfUndirectedEdges > 0)
			throw new GraphException("You can't add a directed edge on an undirected graph!");
		// controllo che i due nodi siano presenti all' interno del grafo, se non ci
		// sono allora li creo
		addEdges(node1, node2, edgeWeight);
	}
	// aggiunta di un arco in un grapho non orientato
	public void addUndirectedEdge(V node1, V node2, E edgeWeight) throws GraphException {
		if (node1 == null || node2 == null || edgeWeight == null)
			throw new GraphException("addUndirectedEdge: parameter cannot be null.");
		if (isDirected() && nOfEdges > 0)
			throw new GraphException("You can't add an undirected edge on an directed graph!");
		addEdges(node1, node2, edgeWeight);
		addEdges(node1, node2, edgeWeight);
		nOfUndirectedEdges += 2;
	}
	
	// verifica se il grafo è diretto
	public boolean isDirected() {
		return (nOfEdges != nOfUndirectedEdges);
	}
	
	// verifica se il grafo contiene un dato nodo
	public boolean containsNode(V node) throws GraphException {
		if (node == null)
		throw new GraphException("containsNode: node parameter cannot be null");
		return gr.containsKey(node);
	}
	
	// verifica se il grafo contiene un dato arco
	public boolean containsEdge(V startNode, V endNode, E edgeWeight) throws GraphException {
		if (startNode == null || endNode == null || edgeWeight == null)
			throw new GraphException("containsEdge: parameter cannot be null");
		if (!(containsNode(startNode))) // controlla se il nodo e` presente
			return false;
		Edge<V, E> edge = new Edge<>(startNode, endNode, edgeWeight);
		System.out.println(" " + gr.hashCode() + ", " + startNode.hashCode() + ", " + endNode.hashCode() + ", " + edgeWeight.hashCode() + ", " + edge.hashCode());
		System.out.println(gr.get(startNode));
		return true;
		//return gr.get(startNode).containsValue(edge);
	}
	
	// cancellazione di un nodo
	public boolean removeNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("removeNode: node parameter cannot be null");
		if (!(containsNode(node)))
			throw new GraphException("removeNode: node parameter doesn't exist");
		gr.remove(node);
		return true;
	}
	
	// cancellazione di un arco
	// ..........................................
	
	// determinazione del numero di nodi
	public long getNumberOfNodes() {
		return nOfNodes;
	}

	// determinazione del numero di archi
	public long getNumberOfEdges() {
		/* if (!(isDirected()))
			return nOfUndirectedEdges; */
		return nOfEdges;
	}

	// recupero dei nodi del grafo
	public void graphNodes(){
		for (V node : gr.keySet()) {
			System.out.println(node.toString());
		}
	}

	// recupero degli archi del grafo
	public void graphEdges(){
		for (V node : gr.keySet()) {
			System.out.println(gr.get(node).toString());
		}
	}

	// recupero nodi adiacenti di un dato nodo
	// ...........................................

	// recupero etichetta associata a una coppia di nodi
	// ...........................................

	// recupero degli archi DI UN NODO del grafo
	public List<Edge<V, E>> getEdgesFromNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("getEdgesFromNode: node parameter cannot be null");
		if (!gr.containsKey(node))
			throw new GraphException("getEdgesFromNode: node parameter must exist");
		return gr.get(node);
	}
	
	public String toString() {
		String data = "";
		for (V node : gr.keySet()) {
			data += node + " ==> [ " + gr.get(node) + " ]\n";
		}
		return data;
	}
}
