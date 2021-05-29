package graphs;

import org.junit.Test;
import org.junit.Before;
import static org.junit.Assert.assertEquals;
import unionfindset.UnionFindSetException;

public class KruskalAlgorithmTests {
    Graph<String, Float> gr;
    String node1, node2, node3, node4, node5, node6, node7, node8;
    Float weight1, weight2, weight3, weight4, weight5, weight6, weight7, weight8;
    
    @Before
    public void createGraphDirected() {
        node1 = "A";
        node2 = "B";
        node3 = "C";
        node4 = "D";
        node5 = "E";
        node6 = "F";
        node7 = "G";
        node8 = "H";
        gr = new Graph<>("undirected");
        weight1 = 1.11f;
        weight2 = 2.22f;
        weight3 = 3.33f;
        weight4 = 4.44f;
        weight5 = 5.55f;
        weight6 = 6.66f;
        weight7 = 7.77f;
        weight8 = 8.88f;
    }

    @Test
    public void testKruskalUndirected() throws GraphException, UnionFindSetException {
        Graph<String, Float> grTest = new Graph<>("undirected");
        Graph<String, Float> minimumSpanningForest;
        gr.addEdge(node1, node3, weight7);
        gr.addEdge(node1, node5, weight1);
        gr.addEdge(node2, node5, weight7);
        gr.addEdge(node2, node6, weight8);
        gr.addEdge(node3, node5, weight6);
        gr.addEdge(node3, node7, weight3);
        gr.addEdge(node6, node7, weight6);
        gr.addNode(node4);
        gr.addNode(node8);
        minimumSpanningForest = new KruskalAlgorithm<String, Float>().kruskalAlgorithm(gr);
        grTest.addEdge(node1, node5, weight1);
        grTest.addEdge(node3, node7, weight3);
        grTest.addEdge(node3, node5, weight6);
        grTest.addEdge(node6, node7, weight6);
        grTest.addEdge(node2, node5, weight7);
        assertEquals(grTest.graphEdges(), minimumSpanningForest.graphEdges());
    }
}
