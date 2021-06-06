package graphs;

import java.util.List;
import java.util.Collections;
import unionfindset.UnionFindSet;
import unionfindset.UnionFindSetException;

public class KruskalAlgorithm<V, E extends Comparable<E>> {
	/*
  	* It takes as input an undirected graph and returns a minimumSpanningForest (graph).
  	* If a graph is connected the output will be a single tree which will contains
  	* number of edges = number of nodes - 1. If the graph is not connected the output
  	* will be a forest of trees, with number of edges lower than number of nodes - 1.
  	* If the number of nodes of minimumSpanningForest is equals to the number of nodes of
  	* the initial graph all the nodes are already reachable.
  	*/
	public Graph<V, E> kruskal(Graph<V, E> gr) throws GraphException, UnionFindSetException {
		Graph<V, E> minimumSpanningForest = new Graph<>("undirected");
		UnionFindSet<V> grSet = new UnionFindSet<>();
		List<Edge<V, E>> listEdges;

		for (V node : gr.graphNodes()) {
			grSet.makeSet(node);
		}

		listEdges = gr.graphEdges();
		Collections.sort(listEdges);

		for (Edge<V, E> grEdge : listEdges) {
			if (minimumSpanningForest.getNumberOfNodes() == gr.getNumberOfNodes())
				break;
			V firstNode = grSet.find(grEdge.getStartNode());
			V secondNode = grSet.find(grEdge.getEndNode());
			if (!(firstNode.equals(secondNode))) {
				minimumSpanningForest.addEdge(grEdge.getStartNode(), grEdge.getEndNode(), grEdge.getEdgeWeight());
				grSet.union(firstNode, secondNode);
			}
		}
		return minimumSpanningForest;
	}
}
