package graphs;

import java.util.*;
import unionfindset.UnionFindSet;
import unionfindset.UnionFindSetException;

/* prende in input un grafo non orientato e connesso e restituisce una foresta (lista di archi) --- minimumSpanningForest (minima foresta ricoprente) */

public class KruskalAlgorithm <V,E extends Comparable<E>> {
    
	public Graph<V,E> kruskal(Graph<V,E> gr) throws GraphException, UnionFindSetException {
        Graph <V,E> minimumSpanningForest = new Graph<>("undirected");
        UnionFindSet<V> grSet = new UnionFindSet<>();				//mettiamo qui tutti i set creati a riga 17
        List<Edge<V,E>> listEdges;
		
		//crea un albero per ogni nodo (vertice) del grafo
		//prende tutti i nodi del grafo e li inserisce separati (singolarmente)
		for(V node : gr.graphNodes()){
			grSet.makeSet(node);
		}
		
		//ordina gli archi del grafo in senso non decrescente rispetto al peso
		listEdges = gr.graphEdges();
		
		Collections.sort(listEdges);
		
		//per ogni arco preso in ordine di peso non decrescente fare...
		for(Edge<V,E> grEdge : listEdges){
			if (minimumSpanningForest.getNumberOfNodes() == gr.getNumberOfNodes())				// tutti i nodi sono già stati raggiunti
				break;
			V firstNode = grSet.find(grEdge.getStartNode());
			V secondNode = grSet.find(grEdge.getEndNode());
			if (!(firstNode.equals(secondNode))){
				minimumSpanningForest.addEdge(grEdge.getStartNode(), grEdge.getEndNode(), grEdge.getEdgeWeight());
				grSet.union(firstNode, secondNode);
			}
		}
		
		return minimumSpanningForest;
	}
}		
