package graphs;

import java.util.List;
import java.util.LinkedList;
import org.junit.Test;
import org.junit.Before;
import java.util.Collections;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;

public class GraphUndirectedIntegerTests {
	
	Graph<Integer, Double> gr;
	Integer node1, node2, node3, node4;
	
	@Before
	public void createGraphDirected() {
		node1 = 1;
		node2 = 2;
		node3 = 3;
		node4 = 4;
		gr = new Graph<>("undirected");
	}

	@Test
	public void testAddNullNode() throws GraphException {
		try {
			gr.addNode(null);
		} catch (GraphException ex) {
			assertEquals("addNode: node parameter cannot be null", ex.getMessage());
		}
	}

	@Test
	public void testAddNullEdge() throws GraphException {
		try {
			gr.addEdge(node1, null, 12.22);
		} catch (GraphException ex) {
			assertEquals("addEdge: parameter cannot be null", ex.getMessage());
		}
	}
	
	@Test
	public void testIsDirected() throws GraphException {
		assertFalse(gr.isDirected());
	}
	
	@Test
	public void testContainsNodeTwoNodes() throws GraphException {
		assertFalse(gr.containsNode(node1));
		assertFalse(gr.containsNode(node2));
	}
	
	@Test
	public void testAddNodeAndContainsNodeTwoNodes() throws GraphException {
		gr.addNode(node1);
		gr.addNode(node2);
		assertTrue(gr.containsNode(node1));
		assertTrue(gr.containsNode(node2));
	}
	
	@Test
	public void testAddEdgeAndContainsEdgeOneEdge() throws GraphException {
		gr.addEdge(node1, node2, 15.55);
		assertTrue(gr.containsEdge(node1, node2));
	}

	@Test
	public void testRemoveNullNode() throws GraphException {
		try {
			gr.removeNode(null);
		} catch (GraphException ex) {
			assertEquals("removeNode: node parameter cannot be null", ex.getMessage());
		}
	}

	@Test
	public void testRemoveNodeNoAdd() throws GraphException {
		assertFalse(gr.removeNode(node1));
		assertFalse(gr.removeNode(node2));
	}

	@Test
	public void testRemoveNodeAndAddNodeFourNodes() throws GraphException {
		gr.addNode(node1);
		gr.addNode(node2);
		gr.addNode(node3);
		gr.addNode(node4);
		assertTrue(gr.removeNode(node1));
		assertFalse(gr.removeNode(node1));
		assertTrue(gr.removeNode(node2));
		assertTrue(gr.removeNode(node3));
		assertTrue(gr.removeNode(node4));
	}

	@Test
	public void testRemoveNullEdge() throws GraphException {
		try {
			gr.addEdge(node1, null, 7.77);
		} catch (GraphException ex) {
			assertEquals("addEdge: parameter cannot be null", ex.getMessage());
		}
	}

	@Test
	public void testRemoveEdgeNoAdd() throws GraphException {
		assertFalse(gr.removeEdge(node1, node2));
		assertFalse(gr.removeEdge(node2, node3));
	}

	@Test
	public void testRemoveEdgeAndAddEdgeFourEdges() throws GraphException {
		gr.addEdge(node1, node2, 55.55);
		gr.addEdge(node2, node1, 9.99);
		gr.addEdge(node3, node4, 8.41);
		gr.addEdge(node4, node2, 11.11);
		assertTrue(gr.removeEdge(node1, node2));
		assertFalse(gr.removeEdge(node2, node1));
		assertTrue(gr.removeEdge(node3, node4));
		assertFalse(gr.removeEdge(node4, node1));
		assertTrue(gr.removeEdge(node4, node2));
		assertFalse(gr.removeEdge(node4, node2));
	}

	@Test
	public void testGetNumberOfNodesAndAddNodeAndRemoveNodeManyNodes() throws GraphException {
		assertEquals(0 , gr.getNumberOfNodes());
		gr.addNode(node1);
		assertEquals(1 , gr.getNumberOfNodes());
		gr.addNode(node2);
		assertEquals(2 , gr.getNumberOfNodes());
		gr.addNode(node2);
		assertEquals(2 , gr.getNumberOfNodes());
		gr.addNode(node3);
		assertEquals(3 , gr.getNumberOfNodes());
		gr.addNode(node4);
		assertEquals(4 , gr.getNumberOfNodes());
		gr.removeNode(node1);
		gr.removeNode(node2);
		gr.removeNode(node3);
		gr.removeNode(node4);
		assertEquals(0 , gr.getNumberOfNodes());
	}

	@Test
	public void testGetNumberOfEdgessAndAddEdgeAndRemoveEdgeManyEdges() throws GraphException {
		assertEquals(0 , gr.getNumberOfEdges());
		gr.addEdge(node1, node2, 22.22);
		assertEquals(1 , gr.getNumberOfEdges());
		gr.addEdge(node2, node3, 87.23);
		assertEquals(2 , gr.getNumberOfEdges());
		gr.addEdge(node2, node3, 87.23);
		assertEquals(2 , gr.getNumberOfEdges());
		gr.addEdge(node1, node4, 98.54);
		assertEquals(3 , gr.getNumberOfEdges());
		gr.addEdge(node4, node3, 54.25);
		assertEquals(4 , gr.getNumberOfEdges());
		gr.removeEdge(node1, node2);
		gr.removeEdge(node2, node3);
		gr.removeEdge(node1, node4);
		gr.removeEdge(node4, node3);
		assertEquals(0 , gr.getNumberOfEdges());
	}

	@Test
	public void testGraphNodesManyNodes() throws GraphException {
		List<Integer> graphNodes = new LinkedList<>();
		assertEquals(graphNodes, gr.graphNodes());
		gr.addNode(node1);
		gr.addNode(node2);
		gr.addNode(node3);
		gr.addNode(node4);
		graphNodes.add(node1);
		graphNodes.add(node2);
		graphNodes.add(node3);
		graphNodes.add(node4);
		assertEquals(graphNodes, gr.graphNodes());
	}

	@Test
	public void testGraphEdgesAndAddManyNodes() throws GraphException {
		List<Edge<Integer, Double>> graphEdges = new LinkedList<>();
		Edge<Integer,Double> edge1 = new Edge<>(node1, node2, 1.12);
		Edge<Integer,Double> edge2 = new Edge<>(node2, node4, 2.23);
		Edge<Integer,Double> edge3 = new Edge<>(node3, node2, 3.34);
		Edge<Integer,Double> edge4 = new Edge<>(node4, node4, 4.45);
		assertEquals(graphEdges, gr.graphNodes());
		gr.addEdge(node1, node2, 1.12);
		gr.addEdge(node2, node4, 2.23);
		gr.addEdge(node3, node2, 3.34);
		gr.addEdge(node4, node4, 4.45);
		//aggiungiamo gli archi (aggiunti al grafo) in una lista di archi
		graphEdges.add(edge1);
		graphEdges.add(edge2);
		graphEdges.add(edge3);
		graphEdges.add(edge4);
		assertEquals(graphEdges, gr.graphEdges());
		assertEquals(4, gr.getNumberOfEdges());
	}

	@Test
	public void testGetAdiacentsFromNodeNoNode() throws GraphException {
		try {
			gr.getAdiacentsFromNode(node1);
		} catch (GraphException ex) {
			assertEquals("getAdiacentsFromNode: node parameter must exist", ex.getMessage());
		}
	}

	@Test
	public void testGetAdiacentsFromNodeAndAddManyNodes() throws GraphException {
		List<Integer> graphNodes = new LinkedList<>();
		List<Integer> graphNodes2 = new LinkedList<>();
		gr.addNode(node1);
		assertEquals(graphNodes, gr.getAdiacentsFromNode(node1));
		gr.addEdge(node1, node2, 1.22);
		gr.addEdge(node2, node2, 2.22);
		gr.addEdge(node3, node2, 3.22);
		gr.addEdge(node4, node4, 4.44);
		graphNodes.add(node2);
		graphNodes2.add(node1);
		graphNodes2.add(node2);
		graphNodes2.add(node3);
		assertEquals(graphNodes, gr.getAdiacentsFromNode(node1));
		assertEquals(graphNodes2, gr.getAdiacentsFromNode(node2));
		assertEquals(graphNodes, gr.getAdiacentsFromNode(node3));
	}
	
	@Test
	public void testGetEdgeWeightNoEdge() throws GraphException {
		try {
			gr.getEdgeWeight(node1, node2);
		} catch (GraphException ex) {
			assertEquals("getEdgesWeight: node parameter must exist", ex.getMessage());
		}
	}

	@Test
	public void testGetEdgeWeightNullEdge() throws GraphException {
		gr.addEdge(node1, node2, 1.22);
		gr.addEdge(node3, node2, 3.22);
		gr.addEdge(node4, node4, 4.44);
		assertEquals(null, gr.getEdgeWeight(node4, node1));
		assertEquals(null, gr.getEdgeWeight(node3, node3));
		assertEquals(null, gr.getEdgeWeight(node3, node1));
	}

	@Test
	public void testGetEdgeFromNoNode() throws GraphException {
		try {
			gr.getEdgesFromNode(node1);
		} catch (GraphException ex) {
			assertEquals("getEdgesFromNode: node parameter must exist", ex.getMessage());
		}
	}
	
	@Test
	public void testGetEdgeFromNode() throws GraphException {
		List<Edge<Integer,Double>> listAllEdgesFromNode1 = new LinkedList<>();
		List<Edge<Integer,Double>> listAllEdgesFromNode2 = new LinkedList<>();
		List<Edge<Integer,Double>> listAllEdgesFromNode3 = new LinkedList<>();
		List<Edge<Integer,Double>> listAllEdgesFromNode4 = new LinkedList<>();
		Edge<Integer,Double> edge1 = new Edge<>(node1, node2, 1.22);
		Edge<Integer,Double> edge1und = new Edge<>(node2, node1, 1.22);
		Edge<Integer,Double> edge2 = new Edge<>(node1, node3, 1.33);
		Edge<Integer,Double> edge2und = new Edge<>(node3, node1, 1.33);
		Edge<Integer,Double> edge3 = new Edge<>(node2, node2, 2.22);
		Edge<Integer,Double> edge3und = new Edge<>(node2, node2, 2.22);
		Edge<Integer,Double> edge4 = new Edge<>(node2, node4, 2.44);
		Edge<Integer,Double> edge4und = new Edge<>(node4, node2, 2.44);
		gr.addEdge(node1, node2, 1.22);
		gr.addEdge(node1, node3, 1.33);
		gr.addEdge(node2, node2, 2.22);
		gr.addEdge(node2, node4, 2.44);
		listAllEdgesFromNode1.add(edge1);
		listAllEdgesFromNode1.add(edge2);
		assertEquals(listAllEdgesFromNode1, gr.getEdgesFromNode(node1));
		listAllEdgesFromNode2.add(edge1und);
		listAllEdgesFromNode2.add(edge3);
		listAllEdgesFromNode2.add(edge3und);
		listAllEdgesFromNode2.add(edge4);
		assertEquals(listAllEdgesFromNode2, gr.getEdgesFromNode(node2));
		listAllEdgesFromNode3.add(edge2und);
		assertEquals(listAllEdgesFromNode3, gr.getEdgesFromNode(node3));
		listAllEdgesFromNode4.add(edge4und);
		assertEquals(listAllEdgesFromNode4, gr.getEdgesFromNode(node4));
	}
	
	@Test
	public void testGetEdgeWeightManyEdges() throws GraphException {
		Edge<Integer,Double> edge1 = new Edge<>(node1, node2, 1.22);
		Edge<Integer,Double> edge2 = new Edge<>(node3, node2, 3.22);
		Edge<Integer,Double> edge3 = new Edge<>(node4, node4, 4.44);
		gr.addEdge(node1, node2, 1.22);
		gr.addEdge(node3, node2, 3.22);
		gr.addEdge(node4, node4, 4.44);
		assertEquals(edge1.getEdgeWeight(), gr.getEdgeWeight(node1, node2));
		assertEquals(edge2.getEdgeWeight(), gr.getEdgeWeight(node3, node2));
		assertEquals(edge3.getEdgeWeight(), gr.getEdgeWeight(node4, node4));
	}

	@Test
	public void testComplete() throws GraphException {
		List<Integer> listNodeRemain = new LinkedList<>();
		gr.addEdge(node1, node2, 1.22);
		gr.addEdge(node4, node1, 4.11);
		gr.addEdge(node2, node4, 2.44);
		gr.addEdge(node1, node3, 1.33);
		gr.addEdge(node2, node3, 2.33);
		gr.addEdge(node4, node4, 2.33);
		assertTrue(gr.removeNode(node4));
		listNodeRemain.add(node1);
		listNodeRemain.add(node2);
		listNodeRemain.add(node3);
		assertEquals(3, gr.getNumberOfNodes());
		assertEquals(3, gr.getNumberOfEdges());
		assertEquals(listNodeRemain, gr.graphNodes());
		assertTrue(gr.removeNode(node1));
		assertEquals(2, gr.getNumberOfNodes());
		assertFalse(gr.removeNode(node1));
		assertEquals(2, gr.getNumberOfNodes());
		assertTrue(gr.removeNode(node2));
		assertEquals(0, gr.getNumberOfEdges());
		listNodeRemain.remove(node1);
		listNodeRemain.remove(node2);
		assertEquals(listNodeRemain, gr.graphNodes());
		assertEquals(1, gr.getNumberOfNodes());
		assertTrue(gr.removeNode(node3));
		assertFalse(gr.removeNode(node4));
	}

	@Test
	public void testSort() throws GraphException {
		List<Edge<Integer,Double>> listNodeSorted = new LinkedList<>();
		Edge<Integer,Double> edge1 = new Edge<>(node3, node4, 5.22);
		Edge<Integer,Double> edge2 = new Edge<>(node3, node2, 3.22);
		Edge<Integer,Double> edge3 = new Edge<>(node1, node2, 9.22);
		Edge<Integer,Double> edge4 = new Edge<>(node4, node4, 4.44);
		gr.addEdge(node3, node4, 5.22);
		gr.addEdge(node3, node2, 3.22);
		gr.addEdge(node1, node2, 9.22);
		gr.addEdge(node4, node4, 4.44);
		listNodeSorted.add(edge2);
		listNodeSorted.add(edge4);
		listNodeSorted.add(edge1);
		listNodeSorted.add(edge3);
		List<Edge<Integer, Double>> listToSort = gr.graphEdges();
        Collections.sort(listToSort); //   ordina gli archi in una sequenza S di pesi crescenti;
		assertEquals(listNodeSorted, listToSort);
	}
}
