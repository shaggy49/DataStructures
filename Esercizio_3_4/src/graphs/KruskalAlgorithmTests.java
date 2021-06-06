package graphs;

import org.junit.Test;
import org.junit.Before;
import static org.junit.Assert.assertEquals;
import unionfindset.UnionFindSetException;

public class KruskalAlgorithmTests {
    Graph<String, Float> gr;
    String node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13, node14, node15, node16, node17, node18;
    Float weight1, weight2, weight3, weight4, weight5, weight6, weight7, weight8, weight9;
    
    @Before
    public void createGraphDirected() {
        gr = new Graph<>("undirected");
        node1 = "A";
        node2 = "B";
        node3 = "C";
        node4 = "D";
        node5 = "E";
        node6 = "F";
        node7 = "G";
        node8 = "H";
        node9 = "I";
        node10 = "J";
        node11 = "K";
        node12 = "L";
        node13 = "M";
        node14 = "N";
        node15 = "O";
        node16 = "P";
        node17 = "Q";
        node18 = "R";
        weight1 = 1.11f;
        weight2 = 2.22f;
        weight3 = 3.33f;
        weight4 = 4.44f;
        weight5 = 5.55f;
        weight6 = 6.66f;
        weight7 = 7.77f;
        weight8 = 8.88f;
        weight9 = 9.99f;
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
        minimumSpanningForest = new KruskalAlgorithm<String, Float>().kruskal(gr);
        grTest.addEdge(node1, node5, weight1);
        grTest.addEdge(node3, node7, weight3);
        grTest.addEdge(node3, node5, weight6);
        grTest.addEdge(node6, node7, weight6);
        grTest.addEdge(node2, node5, weight7);
        assertEquals(grTest.graphEdges(), minimumSpanningForest.graphEdges());
    }

    @Test
    public void testOtherKruskalUndirected() throws GraphException, UnionFindSetException {
        Graph<String, Float> grTest = new Graph<>("undirected");
        Graph<String, Float> minimumSpanningForest;
        gr.addEdge(node1, node18, weight7);
        gr.addEdge(node1, node4, weight4);
        gr.addEdge(node1, node5, weight8);
        gr.addEdge(node2, node18, weight3);
        gr.addEdge(node3, node6, weight9);
        gr.addEdge(node3, node17, weight7);
        gr.addEdge(node4, node18, weight9);
        gr.addEdge(node4, node5, weight1);
        gr.addEdge(node5, node6, weight8);
        gr.addEdge(node5, node8, weight6);
        gr.addEdge(node5, node9, weight3);
        gr.addEdge(node6, node9, weight2);
        gr.addEdge(node6, node10, weight3);
        gr.addEdge(node7, node18, weight1);
        gr.addEdge(node7, node8, weight4);
        gr.addEdge(node8, node9, weight2);
        gr.addEdge(node9, node10, weight4);
        gr.addEdge(node9, node13, weight9);
        gr.addEdge(node10, node13, weight5);
        gr.addEdge(node12, node13, weight8);
        gr.addEdge(node13, node16, weight4);
        gr.addEdge(node13, node17, weight7);
        gr.addEdge(node14, node18, weight4);
        gr.addEdge(node14, node15, weight6);
        gr.addEdge(node15, node16, weight8);
        gr.addEdge(node15, node17, weight3);
        gr.addNode(node11);
        
        minimumSpanningForest = new KruskalAlgorithm<String, Float>().kruskal(gr);
        grTest.addEdge(node4, node5, weight1);
        grTest.addEdge(node7, node18, weight1);
        grTest.addEdge(node6, node9, weight2);
        grTest.addEdge(node8, node9, weight2);
        grTest.addEdge(node2, node18, weight3);
        grTest.addEdge(node5, node9, weight3);
        grTest.addEdge(node6, node10, weight3);
        grTest.addEdge(node15, node17, weight3);
        grTest.addEdge(node1, node4, weight4);
        grTest.addEdge(node7, node8, weight4);
        grTest.addEdge(node13, node16, weight4);
        grTest.addEdge(node14, node18, weight4);
        grTest.addEdge(node10, node13, weight5);
        grTest.addEdge(node14, node15, weight6);
        grTest.addEdge(node3, node17, weight7);
        grTest.addEdge(node12, node13, weight8);      
        assertEquals(grTest.graphEdges(), minimumSpanningForest.graphEdges());
    }
}
