package unionfindset;

import java.util.Comparator;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

public class UnionFindSetTests{

    private Integer i1, i2, i3;
    private UnionFindSet<Integer> unionFindSet;

    @Before
    public void createUnionFindSet() throws UnionFindSetException {
        i1 = 0;
        i2 = 1;
        i3 = 2;
        unionFindSet = new UnionFindSet<Integer>();
    }

    @Test
    public void testMakeSetAndFindOneEl() {
        unionFindSet.makeSet(i1);
        assertEquals(i1, unionFindSet.find(i1));
    }

}
/*
public static void main(String[] args) {

    // setting universe array for simple test
    int[] universe = new int[5];
    for(int i=0; i < universe.length; i++)
        universe[i] = i+1;								

    // create a singleton set for each element of the universe
    for(int i=0; i<universe.length; i++)
        uf.makeSet(universe[i]);
    printSetsInt(universe, uf);

    uf.union(4, 3); // 4 and 3 are in the same set
    printSetsInt(universe, uf);

    uf.union(2, 1); // 1 and 2 are in the same set
    printSetsInt(universe, uf);

    uf.union(1, 3); // 1, 2, 3, 4 are in the same set
    printSetsInt(universe, uf);


    // initialize `UnionFindSet` class for String tests
    UnionFindSet<String> ufS = new UnionFindSet<String>();

    // setting universe array for simple test
    String[] universeString = new String[5];
    for(int i=0; i < universe_string.length; i++)
        universeString[i] = "a" + i;							
    
    for(int i=0; i<universeString.length; i++)
        ufS.makeSet(universeString[i]);
    printSetsString(universeString, ufS);

    ufS.union("a2", "a4");
    printSetsString(universeString, ufS);

}

*/



/* public class OrderedArrayTests {

    private Integer i1, i2, i3;
    private OrderedArray<Integer> orderedArray;

    @Before
    public void createOrderedArray() throws OrderedArrayException {
        i1 = -12;
        i2 = 0;
        i3 = 4;
        orderedArray = new OrderedArray<>(new IntegerComparator());
    }

    @Test
    public void testIsEmpty_zeroEl() {
        assertTrue(orderedArray.isEmpty());
    }

    @Test
    public void testIsEmpty_oneEl() throws Exception {
        orderedArray.add(i1);
        assertFalse(orderedArray.isEmpty());
    }

    @Test
    public void testSize_zeroEl() throws Exception {
        assertEquals(0, orderedArray.size());
    }

    @Test
    public void testSize_oneEl() throws Exception {
        orderedArray.add(i1);
        assertEquals(1, orderedArray.size());
    }

    @Test
    public void testSize_twoEl() throws Exception {
        orderedArray.add(i1);
        orderedArray.add(i2);
        assertEquals(2, orderedArray.size());
    }

    @Test
    public void testAddGet_oneEl() throws Exception {
        orderedArray.add(i1);
        assertTrue(i1 == orderedArray.get(0));
    }

    @Test
    public void testArray_threeEl() throws Exception {

        Integer[] arrExpected = { i1, i2, i3 };

        orderedArray.add(i2);
        orderedArray.add(i1);
        orderedArray.add(i3);

        Integer[] arrActual = new Integer[3];

        for (int i = 0; i < 3; i++)
            arrActual[i] = orderedArray.get(i);

        assertArrayEquals(arrExpected, arrActual);
    }

}
 */