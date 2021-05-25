package graphs;

//V (vertex) tipo delle chiavi (nodi, vertici), E (edge) indica il tipo delle edgeWeight (archi)
public class Edge<V, E> {
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
		if (getClass() != obj.getClass())
			return false;
		Edge <V,E> other = (Edge <V,E>) obj;
		return this.startNode.equals(other.getStartNode()) && this.endNode.equals(other.getEndNode());
	}

	public String toString() {
		return " (" + startNode + " === " + endNode + " : " + edgeWeight + ")";
	}
}
