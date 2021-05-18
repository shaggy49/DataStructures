package unionfindset;

import static org.junit.Assert.assertEquals;
import org.junit.Before;
import org.junit.Test;

public class UnionFindSetStringTests {

    private String i1, i2, i3, i4;
    private UnionFindSet<String> unionFindSet;

    @Before
    public void createUnionFindSet() throws UnionFindSetException {
        i1 = "ciao";
        i2 = "hello";
        i3 = "bonjour";
        i4 = "hola";
        unionFindSet = new UnionFindSet<String>();
    }

    @Test
    public void testMakeSetZeroEl() throws UnionFindSetException {
        try {
            unionFindSet.makeSet(null);
        } catch (UnionFindSetException ex) {
            assertEquals("makeSet method: element parameter cannot be null", ex.getMessage());
        }
    }

    @Test
    public void testFindNullSet() throws UnionFindSetException {
        try {
            unionFindSet.find(null);
        } catch (UnionFindSetException ex) {
            assertEquals("find method: element parameter cannot be null", ex.getMessage());
        }
    }

    @Test
    public void testFindNoSet() throws UnionFindSetException {
        try {
            unionFindSet.find(i1);
        } catch (UnionFindSetException ex) {
            assertEquals("find method: element parameter cannot be null", ex.getMessage());
        }
    }

    @Test
    public void testUnionNullSet() throws UnionFindSetException {
        try {
            unionFindSet.union(null, i1);
        } catch (UnionFindSetException ex) {
            assertEquals("union method: element parameter cannot be null", ex.getMessage());
        }
    }

    @Test
    public void testUnionNoMakeSet() throws UnionFindSetException {
        try {
            unionFindSet.union(i2, i1);
        } catch (UnionFindSetException ex) {
            assertEquals("find method: element parameter cannot be null", ex.getMessage());
        }
    }
    
    @Test
    public void testMakeSetAndFindOneEl() throws UnionFindSetException {
        unionFindSet.makeSet(i1);
        assertEquals(i1, unionFindSet.find(i1));
    }
    
    @Test
    public void testMakeSetTwoTimes() throws UnionFindSetException {
        unionFindSet.makeSet(i1);
        unionFindSet.makeSet(i1);
        assertEquals(i1, unionFindSet.find(i1));
    } 

    @Test
    public void testUnionTwoEl() throws UnionFindSetException {
        unionFindSet.makeSet(i1);
        unionFindSet.makeSet(i2);
        unionFindSet.union(i1, i2);
        assertEquals(unionFindSet.find(i1), unionFindSet.find(i2)); // stesso rappresentate dopo aver fatto la union
    }

    @Test
    public void testUnionManyEl() throws UnionFindSetException {
        unionFindSet.makeSet(i1);
        unionFindSet.makeSet(i2);
        unionFindSet.makeSet(i3);
        unionFindSet.makeSet(i4);
        unionFindSet.union(i2, i1);
        //System.out.println("rappresentante i2 ==> "+unionFindSet.find(i2) + ", rappresentante i1 ==> "+ unionFindSet.find(i1));
        unionFindSet.union(i3, i1);
        //System.out.println("rappresentante i3 ==> "+unionFindSet.find(i3) + ", rappresentante i1 ==> "+ unionFindSet.find(i1));
        unionFindSet.union(i2, i4);
        //System.out.println("rappresentante i2 ==> "+unionFindSet.find(i2) + ", rappresentante i4 ==> "+ unionFindSet.find(i4));
        //arrivato qui avranno tutti e 4 lo stesso rappresentante
        assertEquals(unionFindSet.find(i1), unionFindSet.find(i1));
        assertEquals(unionFindSet.find(i1), unionFindSet.find(i2));
        assertEquals(unionFindSet.find(i1), unionFindSet.find(i3));
        assertEquals(unionFindSet.find(i1), unionFindSet.find(i4));
    }
}
