package graphs;

import java.util.HashMap;
import java.util.List;
import java.util.LinkedList;
import java.util.HashSet;

/* 
 * Creation of an empty graph - O(1)
 * Addition a node - O(1)
 * Addition an edge - O(1)
 * Check if the graph is directed - O(1)
 * Check if the graph contains a given node - O(1) 
 * Check if the graph contains a given edge - O(1) (*)
 * Deletion of a node - O(n) 
 * Deletion of an edge - O(1) (*) 
 * Determination of number of nodes - O(1) 
 * Determination of number of edges - O(n). It solves in O(1)
 * Recovery graph's nodes - O(n)
 * Recovery graph's edges - O(n)
 * Recovery of adjacent nodes of given node - O(1)
 * Recovery of label associated with a pair of nodes - O(1) (*)
 * Recovery of edges of a node of the graph - O(1)
 */

public class Graph<V, E extends Comparable<E>> {
	private HashMap<V, List<Edge<V, E>>> gr;
	private HashSet<Edge<V, E>> setAllEdges;
	private boolean directed;
	private int nOfEdges;

	/* Creation of an empty graph - O(1) */
	public Graph(String answer) {
		if (answer.equalsIgnoreCase("directed"))
			this.directed = true;
		else
			this.directed = false;
		this.nOfEdges = 0;
		this.gr = new HashMap<>();
		this.setAllEdges = new HashSet<>();
	}

	/* Addition a node - O(1) */
	public boolean addNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("addNode: node parameter cannot be null");
		if (!(containsNode(node))) {
			gr.put(node, new LinkedList<>());
			return true;
		}
		return false;
	}

	/* Addition an edge - O(1) */
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
		if (!(directed)) {
			Edge<V, E> ed2 = new Edge<>(node2, node1, edgeWeight);
			gr.get(node2).add(ed2);
		}
		setAllEdges.add(ed1);
		nOfEdges++;
		return true;
	}

	/* Check if the graph is directed - O(1) */
	public boolean isDirected() {
		return this.directed;
	}

	/* Check if the graph contains a given node - O(1) */
	public boolean containsNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("containsNode: node parameter cannot be null");
		return gr.containsKey(node);
	}

	/* Check if the graph contains a given edge - O(1) (*) */
	public boolean containsEdge(V node1, V node2) throws GraphException {
		Edge<V, E> ed1 = new Edge<>(node1, node2, null);
		if (node1 == null || node2 == null)
			throw new GraphException("containsEdge: parameter cannot be null");
		if (!(containsNode(node1)))
			return false;
		if (directed)
			return gr.get(node1).contains(ed1);
		else {
			Edge<V, E> ed2 = new Edge<>(node2, node1, null);
			return gr.get(node1).contains(ed1) && gr.get(node2).contains(ed2);
		}
	}

	/*
	 * Deletion of a node - O(n) If the graph is direct there could be other edges
	 * that have "node" as their final node. Any edge containing this node as the
	 * last node is then deleted.
	 */

	public boolean removeNode(V node) throws GraphException {
		if (node == null)
			throw new GraphException("removeNode: node parameter cannot be null");
		if (!(containsNode(node)))
			return false;
		if (!(directed)) {
			for (V nodeAd : getAdiacentsFromNode(node))
				removeEdge(node, nodeAd);
		} else {
			for (Edge<V, E> edge : graphEdges()) {
				if ((edge.getStartNode()).equals(node) || (edge.getEndNode()).equals(node))
					removeEdge(edge.getStartNode(), edge.getEndNode());
			}
		}
		gr.remove(node);
		return true;
	}

	/* Deletion of an edge - O(1) (*) */
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

	/* Determination of number of nodes - O(1) */
	public int getNumberOfNodes() {
		return gr.size();
	}

	/* Determination of number of edges - O(n). It solves in O(1) */
	public int getNumberOfEdges() {
		return nOfEdges;
	}

	/* Recovery graph's nodes - O(n) */
	public List<V> graphNodes() {
		List<V> listAllNodes = new LinkedList<>();
		for (V node : gr.keySet()) {
			listAllNodes.add(node);
		}
		return listAllNodes;
	}

	/* Recovery graph's edges - O(n) */
	public List<Edge<V, E>> graphEdges() throws GraphException {
		List<Edge<V, E>> listAllEdges = new LinkedList<>();
		for (Edge<V, E> edge : setAllEdges) {
			listAllEdges.add(edge);
		}
		return listAllEdges;
	}

	/*
	 * Recovery of adjacent nodes of given node - O(1). The variable pointToItself
	 * allows to not add an element that points to itself twice in the list of
	 * adiacents
	 */
	public List<V> getAdiacentsFromNode(V node) throws GraphException {
		List<V> listAdiacents = new LinkedList<>();
		boolean pointsToItself = !(directed);
		if (node == null)
			throw new GraphException("getAdiacentsFromNode: node parameter cannot be null");
		if (!(containsNode(node)))
			throw new GraphException("getAdiacentsFromNode: node parameter must exist");

		for (Edge<V, E> edge : gr.get(node)) {
			if (pointsToItself && edge.getStartNode().equals(edge.getEndNode())) {
				pointsToItself = !(pointsToItself);
				continue;
			}
			listAdiacents.add(edge.getEndNode());
		}
		return listAdiacents;
	}

	/* Recovery of label associated with a pair of nodes - O(1) (*) */
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

	/* Recovery of edges of a node of the graph - O(1) */
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
