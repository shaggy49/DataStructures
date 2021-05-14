package unionfindset;

import java.util.HashMap;
import java.util.Map;

/*===========Spiegazioni===========*/
/*
 * Rank == rango -> limite superiore per l' altezza del nodo  
 */

// A class to represent a union_find set
public class UnionFindSet<T> {
	private Map<T, T> parent = new HashMap<T, T>();

	// stores the depth of trees
	private Map<T, Integer> rank = new HashMap<T, Integer>();

	// perform MakeSet operation
	public void makeSet(T element) {
		parent.put(element, element); // x.p = x (dello pseudo-codice)
		rank.put(element, 0); // x.rank = 0 (dello pseudo-codice)
	}

	// Find the root of the set in which element `k` belongs
	public T find(T element) {
		// if `k` is not the root
		if (parent.get(element) != element) { 				// if (x != x.p)
			// path compression
			parent.put(element, find(parent.get(element))); // x.p = FIND-SET(x.p) (da rivedere il perché dell'assegnamento)
		}
		return parent.get(element); // return x.p
	}

	// Perform Union of two subsets
	public void union(T element1, T element2) {
		// find the root of the sets in which elements
		// `el1` and `el2` belongs
		T el1 = find(element1);
		T el2 = find(element2);

		// if `el1` and `el2` are present in the same set
		if (el1 == el2) {
			return;
		}
		link(el1, el2);										//LINK(FIND-SET(x), FIND-SET(y))
	}

	private void link(T element1, T element2) {
		// Always attach a smaller depth tree under the
		// root of the deeper tree.
		if (rank.get(element1) > rank.get(element2)) 		// if(x.rank > y.rank)
			parent.put(element2, element1);					// y.p = x
		else {												
			parent.put(element1, element2);					// x.p = y
			if (rank.get(element1) == rank.get(element2))	// if (x.rank == y.rank)
				rank.put(element2, rank.get(element2) + 1); // y.rank = y.rank + 1
		}
	}

}
