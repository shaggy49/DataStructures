package graphs;

import java.util.List;
import java.util.LinkedList;
import org.junit.Test;
import org.junit.Before;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;

public class GraphDirectedStringTests {
	Graph<String, String> gr;
	String node1, node2, node3, node4;
	
	@Before
	public void createGraphDirected() {
		node1 = "A";
		node2 = "B";
		node3 = "C";
		node4 = "D";
		gr = new Graph<>("directed");
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
			gr.addEdge(node1, null, "weight");
		} catch (GraphException ex) {
			assertEquals("addEdge: parameter cannot be null", ex.getMessage());
		}
	}
	
	@Test
	public void testIsDirected() throws GraphException {
		assertTrue(gr.isDirected());
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
		gr.addEdge(node1, node2, "weight");
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
	public void testRemoveNullEdge() throws GraphException {
		try {
			gr.addEdge(node1, null, "weight");
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
		gr.addEdge(node1, node2, "weight1");
		gr.addEdge(node2, node1, "weight2");
		gr.addEdge(node3, node4, "weight3");
		gr.addEdge(node4, node2, "weight4");
		assertTrue(gr.removeEdge(node1, node2));
		assertFalse(gr.removeEdge(node4, node1));
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
		gr.addEdge(node1, node2, "weight1");
		assertEquals(1 , gr.getNumberOfEdges());
		gr.addEdge(node2, node3, "weight2");
		assertEquals(2 , gr.getNumberOfEdges());
		gr.addEdge(node2, node3, "weight2");
		assertEquals(2 , gr.getNumberOfEdges());
		gr.addEdge(node1, node4, "weight3");
		assertEquals(3 , gr.getNumberOfEdges());
		gr.addEdge(node4, node3, "weight4");
		assertEquals(4 , gr.getNumberOfEdges());
		gr.removeEdge(node1, node2);
		gr.removeEdge(node2, node3);
		gr.removeEdge(node1, node4);
		gr.removeEdge(node4, node3);
		assertEquals(0 , gr.getNumberOfEdges());		
		gr.addEdge(node1, node2, "weight1");
		gr.addEdge(node1, node3, "weight4");
		gr.addEdge(node4, node1, "weight2");
		gr.addEdge(node2, node4, "weight3");
		gr.addEdge(node2, node3, "weight5");
		assertTrue(gr.removeNode(node1));
		assertTrue(gr.removeNode(node2));
	}
	
	@Test
	public void testGraphNodesManyNodes() throws GraphException {
		List<String> graphNodes = new LinkedList<>();
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
		List<Edge<String, String>> graphEdges = new LinkedList<>();
		Edge<String,String> edge1 = new Edge<>(node1, node2, "weight1");
		Edge<String,String> edge2 = new Edge<>(node2, node4, "weight2");
		Edge<String,String> edge3 = new Edge<>(node3, node2, "weight3");
		Edge<String,String> edge4 = new Edge<>(node4, node4, "weight4");
		assertEquals(graphEdges, gr.graphNodes());
		gr.addEdge(node1, node2, "weight1");
		gr.addEdge(node2, node4, "weight2");
		gr.addEdge(node3, node2, "weight3");
		gr.addEdge(node4, node4, "weight4");
		graphEdges.add(edge1);
		graphEdges.add(edge2);
		graphEdges.add(edge3);
		graphEdges.add(edge4);
		assertEquals(graphEdges, gr.graphEdges());
		gr.removeEdge(node1, node2);
		graphEdges.remove(edge1);
		assertEquals(graphEdges, gr.graphEdges());
		assertEquals(3, gr.getNumberOfEdges());
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
		List<Edge<String,String>> listAllEdgesFromNode1 = new LinkedList<>();
		List<Edge<String,String>> listAllEdgesFromNode2 = new LinkedList<>();
		List<Edge<String,String>> listAllEdgesFromNode34 = new LinkedList<>();
		Edge<String,String> edge1 = new Edge<>(node1, node2, "weight1");
		Edge<String,String> edge2 = new Edge<>(node1, node3, "weight2");
		Edge<String,String> edge3 = new Edge<>(node2, node2, "weight3");
		Edge<String,String> edge4 = new Edge<>(node2, node4, "weight4");
		gr.addEdge(node1, node2, "weight1");
		gr.addEdge(node1, node3, "weight2");
		gr.addEdge(node2, node2, "weight3");
		gr.addEdge(node2, node4, "weight4");
		listAllEdgesFromNode1.add(edge1);
		listAllEdgesFromNode1.add(edge2);
		assertEquals(listAllEdgesFromNode1, gr.getEdgesFromNode(node1));
		listAllEdgesFromNode2.add(edge3);
		listAllEdgesFromNode2.add(edge4);
		assertEquals(listAllEdgesFromNode2, gr.getEdgesFromNode(node2));
		assertEquals(listAllEdgesFromNode34, gr.getEdgesFromNode(node3));
		assertEquals(listAllEdgesFromNode34, gr.getEdgesFromNode(node4));
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
		List<String> graphNodes = new LinkedList<>();
		gr.addNode(node1);
		assertEquals(graphNodes, gr.getAdiacentsFromNode(node1));
		gr.addEdge(node1, node2, "weight1");
		gr.addEdge(node2, node2, "weight2");
		gr.addEdge(node3, node2, "weight3");
		gr.addEdge(node4, node4, "weight4");
		graphNodes.add(node2);
		assertEquals(graphNodes, gr.getAdiacentsFromNode(node1));
		assertEquals(graphNodes, gr.getAdiacentsFromNode(node2));
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
		gr.addEdge(node1, node2, "weight1");
		gr.addEdge(node3, node2, "weight3");
		gr.addEdge(node4, node4, "weight4");
		assertEquals(null, gr.getEdgeWeight(node2, node1));
		assertEquals(null, gr.getEdgeWeight(node3, node3));
		assertEquals(null, gr.getEdgeWeight(node4, node1));
	}
	
	@Test
	public void testGetEdgeWeightManyEdges() throws GraphException {
		Edge<String,String> edge1 = new Edge<>(node1, node2, "weight1");
		Edge<String,String> edge2 = new Edge<>(node2, node1, "weight2");
		Edge<String,String> edge3 = new Edge<>(node3, node2, "weight3");
		Edge<String,String> edge4 = new Edge<>(node4, node4, "weight4");
		gr.addEdge(node1, node2, "weight1");
		gr.addEdge(node2, node1, "weight2");
		gr.addEdge(node3, node2, "weight3");
		gr.addEdge(node4, node4, "weight4");
		assertEquals(edge1.getEdgeWeight(), gr.getEdgeWeight(node1, node2));
		assertEquals(edge2.getEdgeWeight(), gr.getEdgeWeight(node2, node1));
		assertEquals(edge3.getEdgeWeight(), gr.getEdgeWeight(node3, node2));
		assertEquals(edge4.getEdgeWeight(), gr.getEdgeWeight(node4, node4));
	}
	
	@Test
	public void testComplete() throws GraphException {
		List<String> listNodeRemain = new LinkedList<>();
		gr.addEdge(node1, node2, "weight1");
		gr.addEdge(node4, node1, "weight2");
		gr.addEdge(node2, node4, "weight3");
		gr.addEdge(node1, node3, "weight4");
		gr.addEdge(node2, node3, "weight5");
		gr.addEdge(node4, node4, "weight6");
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
}
