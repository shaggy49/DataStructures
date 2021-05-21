// package graphs

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

	public E getedgeWeight() {
		return edgeWeight;
	}

	public boolean equals(V otherStartNode, V otherEndNode) {
		return this.startNode.equals(otherStartNode) && this.endNode.equals(otherEndNode);
	}

	@Override
	public int hashCode() {
		return startNode.hashCode();
	}

	public String toString() {
		return " (" + startNode + " ==> " + endNode + " : " + edgeWeight + ") ";
	}
}
