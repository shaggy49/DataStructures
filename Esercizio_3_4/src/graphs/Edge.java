package graphs;

import java.util.*;

//V (vertex) tipo delle chiavi (nodi, vertici), E (edge) indica il tipo delle edgeWeight (archi)

public class Edge<V, E extends Comparable<E>> implements Comparable<Edge<V,E>> {
//public class Edge<V, E> {
	private V startNode;
	private V endNode;
	private E edgeWeight;

	public Edge(V startNode, V endNode, E edgeWeight) {
		this.startNode = startNode;
		this.endNode = endNode;
		this.edgeWeight = edgeWeight;
	}

	public V getStartNode() {
		return this.startNode;
	}

	public V getEndNode() {
		return endNode;
	}

	public E getEdgeWeight() {
		return edgeWeight;
	}

	@Override
	public boolean equals(Object obj) {
		//return this.startNode.equals(edge2.getStartNode()) && this.endNode.equals(edge2.getEndNode());
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Edge <V,E> other = (Edge <V,E>) obj;
		return this.startNode.equals(other.getStartNode()) && this.endNode.equals(other.getEndNode());
	}
 
	@Override
	public int compareTo(Edge<V,E> edge) {
		return (this.getEdgeWeight()).compareTo(edge.getEdgeWeight());
	}

	public String toString() {
		return " (" + startNode + " === " + endNode + " : " + edgeWeight + ")";
	}
}
