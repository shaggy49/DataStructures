package graphs;

import java.util.List;
import java.util.LinkedList;
import org.junit.Test;
import org.junit.Before;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;

public class GraphIntegerTests {
	
	Graph<Integer, Integer> gr;
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
			gr.addEdge(node1, null, 12);
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
		gr.addEdge(node1, node2, 15);
		assertTrue(gr.containsEdge(node1, node2, 15));
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
			gr.addEdge(node1, null, 7);
		} catch (GraphException ex) {
			assertEquals("addEdge: parameter cannot be null", ex.getMessage());
		}
	}

	@Test
	public void testRemoveEdgeNoAdd() throws GraphException {
		assertFalse(gr.removeEdge(node1, node2, 5));
		assertFalse(gr.removeEdge(node2, node3, 20));
	}

	@Test
	public void testRemoveEdgeAndAddEdgeFourEdges() throws GraphException {
		gr.addEdge(node1, node2, 55);
		gr.addEdge(node2, node1, 9);
		gr.addEdge(node3, node4, 841);
		gr.addEdge(node4, node2, 11);
		assertTrue(gr.removeEdge(node1, node2, 55));
		assertFalse(gr.removeEdge(node2, node1, 60));
		assertTrue(gr.removeEdge(node3, node4, 841));
		assertFalse(gr.removeEdge(node4, node1, 5));
		assertTrue(gr.removeEdge(node4, node2, 11));
		assertFalse(gr.removeEdge(node4, node2, 55));
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
		gr.addEdge(node1, node2, 22);
		assertEquals(1 , gr.getNumberOfEdges());
		gr.addEdge(node2, node3, 87);
		assertEquals(2 , gr.getNumberOfEdges());
		gr.addEdge(node2, node3, 87);
		assertEquals(2 , gr.getNumberOfEdges());
		gr.addEdge(node1, node4, 98);
		assertEquals(3 , gr.getNumberOfEdges());
		gr.addEdge(node4, node3, 54);
		assertEquals(4 , gr.getNumberOfEdges());
		gr.removeEdge(node1, node2, 22);
		gr.removeEdge(node2, node3, 87);
		gr.removeEdge(node1, node4, 98);
		gr.removeEdge(node4, node3, 54);
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
		List<Edge<Integer, Integer>> graphEdges = new LinkedList<>();
		assertEquals(graphEdges, gr.graphNodes());
		gr.addEdge(node1, node2, 112);
		gr.addEdge(node2, node4, 223);
		gr.addEdge(node4, node4, 445);
		Edge<Integer,Integer> edge1 = new Edge<>(node1, node2, 112);
		Edge<Integer,Integer> edge2 = new Edge<>(node2, node1, 112);
		Edge<Integer,Integer> edge3 = new Edge<>(node2, node4, 223);
		Edge<Integer,Integer> edge4 = new Edge<>(node4, node2, 223);
		Edge<Integer,Integer> edge5 = new Edge<>(node4, node4, 445);
		graphEdges.add(edge1);
		graphEdges.add(edge2);
		graphEdges.add(edge3);
		graphEdges.add(edge4);
		graphEdges.add(edge5);
		graphEdges.add(edge5);
		assertEquals(graphEdges, gr.graphEdges());
	}

	@Test
	public void testGetAdiacentsFromNodeNoNode() throws GraphException {
		try {
			gr.getAdiacentsFromNode(node1);
		} catch (GraphException ex) {
			assertEquals("getAdiacentsFromNode: node parameter must exist", ex.getMessage());
		}
	}

	//---------------------------------funziona ma da rivedere se è sensato così------------------------------
	@Test
	public void testGetAdiacentsFromNodeAndAddManyNodes() throws GraphException {
		List<Integer> graphNodes = new LinkedList<>();
		List<Integer> graphNodes2 = new LinkedList<>();
		gr.addNode(node1);
		assertEquals(graphNodes, gr.getAdiacentsFromNode(node1));
		gr.addEdge(node1, node2, 111);
		gr.addEdge(node2, node2, 222);
		gr.addEdge(node3, node2, 333);
		gr.addEdge(node4, node4, 444);
		graphNodes.add(node1);
		graphNodes.add(node3);
		assertEquals(graphNodes, gr.getAdiacentsFromNode(node2));
		assertEquals(graphNodes2, gr.getAdiacentsFromNode(node4));
	}
	
	@Test
	public void testGetEdgeWeightNoEdge() throws GraphException {
		try {
			gr.getEdgeWeight(node1, node2);
		} catch (GraphException ex) {
			assertEquals("gedEdgesWeight: node parameter must exist", ex.getMessage());
		}
	}

	@Test
	public void testGetEdgeWeightNullEdge() throws GraphException {
		gr.addEdge(node1, node2, 122);
		gr.addEdge(node3, node2, 322);
		gr.addEdge(node4, node4, 444);
		assertEquals(null, gr.getEdgeWeight(node4, node1));
		assertEquals(null, gr.getEdgeWeight(node3, node3));
		assertEquals(null, gr.getEdgeWeight(node3, node1));
	}

	@Test
	public void testGetEdgeWeightManyEdges() throws GraphException {
		Edge<Integer,Integer> edge1 = new Edge<>(node1, node2, 122);
		Edge<Integer,Integer> edge2 = new Edge<>(node3, node2, 322);
		Edge<Integer,Integer> edge3 = new Edge<>(node4, node4, 444);
		gr.addEdge(node1, node2, 122);
		gr.addEdge(node3, node2, 322);
		gr.addEdge(node4, node4, 444);
		assertEquals(edge1.getEdgeWeight(), gr.getEdgeWeight(node1, node2));
		assertEquals(edge2.getEdgeWeight(), gr.getEdgeWeight(node3, node2));
		assertEquals(edge3.getEdgeWeight(), gr.getEdgeWeight(node4, node4));
	}
}
