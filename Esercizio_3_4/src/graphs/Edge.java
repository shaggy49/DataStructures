package graphs;

public class Edge<V, E extends Comparable<E>> implements Comparable<Edge<V, E>> {
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
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (this.getClass() != obj.getClass())
			return false;
		Edge<V, E> other = (Edge<V, E>) obj;
		return this.startNode.equals(other.getStartNode()) && this.endNode.equals(other.getEndNode());
	}

	/*
	 * This class overrides equals(Object) method so it's necessaty to override the
	 * hashCode() method because the general contract for the hashCode() method,
	 * which states that equal objects must have equal hash codes.
	 */
	@Override
	public int hashCode() {
		return startNode.hashCode();
	}

	@Override
	public int compareTo(Edge<V, E> edge) {
		return (this.getEdgeWeight()).compareTo(edge.getEdgeWeight());
	}

	public String toString() {
		return " (" + startNode + " === " + endNode + " : " + edgeWeight + ")";
	}
}
