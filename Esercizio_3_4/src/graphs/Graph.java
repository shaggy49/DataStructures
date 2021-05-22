// package graphs

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

/* Creazione di un grafo vuoto – O(1)
 * Aggiunta di un nodo – O(1) 							------FATTO------
 * Aggiunta di un arco – O(1)							------FATTO------
 * Verifica se il grafo è diretto – O(1)				------FATTO------
 * Verifica se il grafo contiene un dato nodo – O(1)	------FATTO------
 * Verifica se il grafo contiene un dato arco – O(1)  (*) ------FATTO----
 * Cancellazione di un nodo – O(n)						------FATTO------ (unico che manca: non va bene per archi non diretti)
 * Cancellazione di un arco – O(1)  (*)				------FATTO------
 * Determinazione del numero di nodi – O(1)			------FATTO------
 * Determinazione del numero di archi – O(n)			------FATTO------
 * Recupero dei nodi del grafo – O(n)					------FATTO------
 * Recupero degli archi del grafo – O(n)				------FATTO------
 * Recupero nodi adiacenti di un dato nodo – O(1)  (*)	-----FATTO-------
 * Recupero etichetta associata a una coppia di nodi – O(1) (*) ---FATTO-----
 */

// V (vertex) tipo delle chiavi (nodi, vertici) 

public class Graph<V, E> {
	private Map<V, List<Edge<V, E>>> gr;
	private long nOfNodes = 0;
	private long nOfEdges = 0; 
	private boolean directed = false;

	public Graph(String answer) {
		if(answer == "directed" || answer == "Directed"){
			this.directed = true;
		}
		//in ogni altro caso, se non specificato dal cliente il grafo sarà non orientato
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

	// aggiunta di un arco (gestire caso in cui l'arco è già presente)
	public boolean addEdge(V node1, V node2, E edgeWeight) throws GraphException {
		if (node1 == null || node2 == null || edgeWeight == null)
			throw new GraphException("addEdge: parameter cannot be null");
		if (!gr.containsKey(node1))
			addNode(node1);
		if (!gr.containsKey(node2))
			addNode(node2);
		if(containsEdge(node1, node2))
			return false; //vedere se conviene lanciare un'eccezione (anche se mi sembra un po' too much)
		if(directed)
			gr.get(node1).add(new Edge<>(node1, node2, edgeWeight)); 
		else{
			gr.get(node1).add(new Edge<>(node1, node2, edgeWeight)); 
			gr.get(node2).add(new Edge<>(node2, node1, edgeWeight)); 
		}
		nOfEdges++;
		return true;
	}

	//metodo che ritorna true se l'arco è già contenuto nel grafo
	private boolean containsEdge(V node1, V node2) throws GraphException{
		if (!(containsNode(node1)))
			return false;
		List<Edge<V,E>> listNode = gr.get(node1);
		for(Edge<V,E> ed : listNode){
			if(node1.equals(ed.getStartNode()) && node2.equals(ed.getEndNode()))
				return true;
		}
		return false;
	}

	// verifica se il grafo è diretto
	public boolean isDirected() {
		return this.directed;
	}
	
	// verifica se il grafo contiene un dato nodo
	public boolean containsNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("containsNode: node parameter cannot be null");
		return gr.containsKey(node);
	}
	
	// verifica se il grafo contiene un dato arco
	public boolean containsEdge(V node1, V node2, E edgeWeight) throws GraphException {
		if (node1 == null || node2 == null || edgeWeight == null)
			throw new GraphException("containsEdge: parameter cannot be null");
		if (!(containsNode(node1))) // controlla se il nodo e` presente
			return false;
		Edge<V, E> ed = new Edge<>(node1, node2, edgeWeight);
		if(directed)
			return gr.get(node1).contains(ed);
		else{
			Edge<V, E> ed1 = new Edge<>(node2, node1, edgeWeight);
			return gr.get(node1).contains(ed) || gr.get(node2).contains(ed1);
		}
	}
	
	/* 
	* Manca gestire il caso il grafo non sia diretto
	*/
	// cancellazione di un nodo
	public boolean removeNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("removeNode: node parameter cannot be null");
		if (!(containsNode(node)))
			return false;
		//elimino prima tutti gli archi del nodo
		Iterator<Edge<V,E>> edgeIterator = gr.get(node).iterator();
		if(directed){
			while( edgeIterator.hasNext()){
				edgeIterator.next();
				edgeIterator.remove();
				nOfEdges--;
			}
		}
/*		TODO: gestire caso degli archi non orientati (rimuovere anche l'inverso)
 		else{
			while( edgeIterator.hasNext()){
				edgeIterator.next();
				edgeIterator.remove();
				nOfEdges--;
			}
		}
 */		//rimuovo poi il nodo effettivo
		gr.remove(node);
		nOfNodes--;
		return true;
	}	
	
	//cancellazione di un arco (gestire caso in cui l'arco non sia presente)
	public void removeEdge(V node1, V node2, E edgeWeight) throws GraphException{
		if (node1 == null || node2 == null || edgeWeight == null)
			throw new GraphException("removeEdge: parameter cannot be null");
		if(!containsEdge(node1, node2, edgeWeight))
			throw new GraphException("removeEdge: edge's not contained in the graph");
		Edge<V, E> ed = new Edge<>(node1, node2, edgeWeight);
		if(directed)
			gr.get(node1).remove(ed);
		else{
			Edge<V, E> ed1 = new Edge<>(node2, node1, edgeWeight);
			gr.get(node1).remove(ed);
			gr.get(node2).remove(ed1);
		}
		nOfEdges--;
	}

	// determinazione del numero di nodi
	public long getNumberOfNodes() {
		return nOfNodes;
	}

	// determinazione del numero di archi
	public long getNumberOfEdges() {
		return nOfEdges;
	}

	// recupero dei nodi del grafo 
	public List<V> graphNodes(){
		List<V> listAllNodes = new LinkedList<>();
		for (V node : gr.keySet()) {
			listAllNodes.add(node);
		}
		return listAllNodes;
	}

	// recupero degli archi del grafo 
	public List<Edge<V,E>> graphEdges(){
		List<Edge<V,E>> listAllEdges = new LinkedList<>();
		for (List<Edge<V,E>> listNode : gr.values()) {
			for(Edge<V,E> edge : listNode){
				listAllEdges.add(edge);
			}
		}
		return  listAllEdges;
	}

	// recupero nodi adiacenti di un dato nodo
	public List<V> getAdiacentsFromNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("getEdgesFromNode: node parameter cannot be null");
		if (!gr.containsKey(node))
			throw new GraphException("getEdgesFromNode: node parameter must exist");
		List<V> listAdiacents = new LinkedList<>();
		for(Edge<V,E> edge : gr.get(node)){
			listAdiacents.add(edge.getEndNode());
		}
		return listAdiacents;
	}

	// recupero etichetta associata a una coppia di nodi
	public E getEdgeWeight(V node1, V node2) throws GraphException{
		if (node1 == null || node2 == null)
			throw new GraphException("getEdgesWeight: node parameter cannot be null");
		if (!(containsNode(node1)) || !(containsNode(node2)))
			throw new GraphException("gedEdgesWeight: edge is not contained in the graph");
		List<Edge<V,E>> listNode = gr.get(node1);
		for(Edge<V,E> ed : listNode){
			if(node1.equals(ed.getStartNode()) && node2.equals(ed.getEndNode()))
				return ed.getEdgeWeight();
		}
		return null;
	}

	// recupero degli archi	di un nodo del grafo
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
