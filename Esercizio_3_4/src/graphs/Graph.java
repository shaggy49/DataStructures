package graphs;

import java.util.HashMap;
import java.util.List;
import java.util.LinkedList;
import java.util.HashSet;

/* 
 * Creazione di un grafo vuoto – O(1)
 * Aggiunta di un nodo – O(1) 							------FATTO------
 * Aggiunta di un arco – O(1)							------FATTO------
 * Verifica se il grafo è diretto – O(1)				------FATTO------
 * Verifica se il grafo contiene un dato nodo – O(1)	------FATTO------
 * Verifica se il grafo contiene un dato arco – O(1)  (*) ----FATTO------
 * Cancellazione di un nodo – O(n)						------FATTO------
 * Cancellazione di un arco – O(1)  (*)					------FATTO------
 * Determinazione del numero di nodi – O(1)				------FATTO------
 * Determinazione del numero di archi – O(n)			------FATTO------
 * Recupero dei nodi del grafo – O(n)					------FATTO------
 * Recupero degli archi del grafo – O(n)				------FATTO------
 * Recupero nodi adiacenti di un dato nodo – O(1)  (*)	-----FATTO-------
 * Recupero etichetta associata a una coppia di nodi – O(1) (*) ---FATTO-----
 */

// V (vertex) tipo delle chiavi (nodi, vertici) 

public class Graph<V, E extends Comparable<E>> {
	private HashMap<V, List<Edge<V, E>>> gr = null;			//implementa l'interfaccia Map<K,V> quindi implementa tutti i metodi dell'interfaccia Map<K, V>. Gli unici metodi in più della classe HashMap<K,V> sono i costruttori
	private long nOfEdges = 0;
	private boolean directed = false;
	//private HashMap<Edge<V,E>, Edge<V, E>> setAllEdges;
	private HashSet<Edge<V,E>> setAllEdges = null;				// The underlying data structure for HashSet is hashtable. Vogliamo che dato un arco come indice ci ritorni effettivamente l'arco. Questo non si può fare con le liste perché hanno remove con complessità O(N)
	
	// creazione di un grafo vuoto - O(1)
	public Graph(String answer) {
		if (answer.equalsIgnoreCase("directed"))
			this.directed = true;
		// in ogni altro caso, se non specificato dal cliente il grafo sarà non orientato
		else
			this.directed = false;
		this.nOfEdges = 0;
		this.gr = new HashMap<>();
		this.setAllEdges = new HashSet<>();
	}

	// aggiunta di un nodo - O(1)
	public boolean addNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("addNode: node parameter cannot be null");
		if (!(containsNode(node))) {
			gr.put(node, new LinkedList<>()); // inserisco in node una nuova lista vuota: node --> LinkedList(0)
			return true;
		}
		return false;
	}

	// aggiunta di un arco - O(1)
	public boolean addEdge(V node1, V node2, E edgeWeight) throws GraphException {
		Edge<V, E> ed1 = new Edge<>(node1, node2, edgeWeight);
		if (node1 == null || node2 == null || edgeWeight == null)
			throw new GraphException("addEdge: parameter cannot be null");
		if (!(containsNode(node1)))
			addNode(node1);
		if (!(containsNode(node2)))
			addNode(node2);
		if (containsEdge(node1, node2))
			return false;
		gr.get(node1).add(ed1);
		if (!(directed)){
			Edge<V, E> ed2 = new Edge<>(node2, node1, edgeWeight);
			gr.get(node2).add(ed2);
		}
		setAllEdges.add(ed1);
		nOfEdges++;
		return true;
	}

	// verifica se il grafo è diretto - O(1)
	public boolean isDirected() {
		return this.directed;
	}

	// verifica se il grafo contiene un dato nodo - O(1)
	public boolean containsNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("containsNode: node parameter cannot be null");
		return gr.containsKey(node);
	}

	// verifica se il grafo contiene un dato arco - O(1) (*) ---> l'asterisco è dovuto al contains!!! quindi il get(node1) e get(node2) restituirà pochi valori ---> O(1)
	public boolean containsEdge(V node1, V node2) throws GraphException {
		Edge<V, E> ed1 = new Edge<>(node1, node2, null);
		if (node1 == null || node2 == null)
			throw new GraphException("containsEdge: parameter cannot be null");
		if (!(containsNode(node1))) // controlla se il nodo e` presente
			return false;
		if (directed)
			return gr.get(node1).contains(ed1);
		else {
			Edge<V, E> ed2 = new Edge<>(node2, node1, null);
			return gr.get(node1).contains(ed1) && gr.get(node2).contains(ed2); //controlla il valore e non la chiava(per questo e` O(n))
		}
	}

	// cancellazione di un nodo - O(n)
	public boolean removeNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("removeNode: node parameter cannot be null");
		if (!(containsNode(node)))
			return false;
		//lo facciamo perche` abbiamo meno elementi ed e` piu` efficiente
		if (!(directed)) {
			// elimino tutti gli archi del nodo --> dovrebbe essere più veloce di quello sopra nell'ipotesi in cui non ci siano tanti nodi sconnessi tra loro
			for (V nodeAd : getAdiacentsFromNode(node))
				removeEdge(node, nodeAd);
		}
		/*
		* se il grafo è diretto potrebbero esserci altri archi che hanno "node"
		* come nodo finale. Quindi elimino qualsiasi arco contenga questo nodo come
		* ultimo nodo
		*/
		else {
			for (Edge<V, E> edge : graphEdges()) {
				if ((edge.getStartNode()).equals(node) || (edge.getEndNode()).equals(node))
					removeEdge(edge.getStartNode(), edge.getEndNode());
			}
		}
		// rimuovo poi il nodo effettivo
		gr.remove(node);
		return true;
	}

	// cancellazione di un arco - O(1) (*) ---> va bene ma solo per grafi sparsi (perche` assumiamo che un nodo abbiamo pochi archi)
	//---> l'asterisco è dovuto al remove!!! quindi il get(node1) e get(node2) restituirà pochi valori ---> O(1)
	public boolean removeEdge(V node1, V node2) throws GraphException {
		Edge<V, E> edge = new Edge<>(node1, node2, null);
		if (node1 == null || node2 == null)
			throw new GraphException("removeEdge: parameter cannot be null");
		if (!(containsEdge(node1, node2)))
			return false;
		gr.get(node1).remove(edge);
		if (!(directed)) {
			Edge<V, E> ed1 = new Edge<>(node2, node1, null);
			gr.get(node2).remove(ed1);
		}
		setAllEdges.remove(edge);
		nOfEdges--;
		return true;
	}

	// determinazione del numero di nodi - O(1)
	public long getNumberOfNodes() {
		return gr.size();				//numero di chiavi(tipo nodo) inserite nel grafo (che è HashMap<>)
	}

	// determinazione del numero di archi - O(n)
	public long getNumberOfEdges() {
		return nOfEdges;				//altrimenti: si scorrono tutti i nodi e si conta il numero di elementi della lista (listAllNodes.size())
	}

	// recupero dei nodi del grafo - O(n)
	public List<V> graphNodes() {
		List<V> listAllNodes = new LinkedList<>();	//LinkedList implementa u
		for (V node : gr.keySet()) {
			listAllNodes.add(node);
		}
		return listAllNodes;
	}

	// recupero degli archi del grafo - O(n)
	public List<Edge<V, E>> graphEdges() throws GraphException {
		List<Edge<V,E>> listAllEdges = new LinkedList<>();
		for (Edge<V,E> edge : setAllEdges) {
			listAllEdges.add(edge);
		}		
		return listAllEdges;
	}

	// recupero nodi adiacenti di un dato nodo - O(1) (*) -------> motivazione: se il grafo è sparso si avranno pochi archi associati a un nodo --> il for a riga 196 può considerarsi con tempo costante
	public List<V> getAdiacentsFromNode(V node) throws GraphException {
		List<V> listAdiacents = new LinkedList<>();
		boolean pointsToItself = !(directed);	//caso in cui il grafo é non diretto e un elemento punta a se stesso, non vogliamo aggiungerlo due volte nella sua lista di adiacenza
		if (node == null)
			throw new GraphException("getAdiacentsFromNode: node parameter cannot be null");
		if (!(containsNode(node)))
			throw new GraphException("getAdiacentsFromNode: node parameter must exist");
		
		for (Edge<V, E> edge : gr.get(node)){
			if (pointsToItself && edge.getStartNode().equals(edge.getEndNode())){		//qui ci entra solo una volta solo se il grafo è non diretto e c'è un elemnto che punta a se stesso
				pointsToItself = !(pointsToItself);										//non lo aggiungiamo perché tanto ci torneremo visto che aggiungiamo due archi che vanno e partono dallo stesso nodo
				continue;
			}
			listAdiacents.add(edge.getEndNode());
		}
		return listAdiacents;
	}

	// recupero etichetta associata a una coppia di nodi - O(1) (*) -------> vedi sopra
	public E getEdgeWeight(V node1, V node2) throws GraphException {
		if (node1 == null || node2 == null)
			throw new GraphException("getEdgesWeight: node parameter cannot be null");
		if (!(containsNode(node1)) || !(containsNode(node2)))
			throw new GraphException("getEdgesWeight: node parameter must exist");
		for (Edge<V, E> edge : gr.get(node1)) {
			if (node2.equals(edge.getEndNode()))
				return edge.getEdgeWeight();
		} 
		return null;
	}

	//NON RICHIESTO, MA IMPLEMENTATO LO STESSO PERCHÉ POTREBBE SERVIRE A UN UTENTE ---> NON LO CHIAMIAMO MAI PERCHÉ LO DOVREMMO CHIAMARE CON UN NODO SU CUI ABBIAMO GIÀ TESTATO SE IL NODO SIA NULLO E SE È CONTENUTO
	// recupero degli archi di un nodo del grafo - O(1)
	public List<Edge<V, E>> getEdgesFromNode(V node) throws GraphException { 
		if (node == null)
			throw new GraphException("getEdgesFromNode: node parameter cannot be null");
		if (!(containsNode(node)))
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
