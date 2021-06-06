package unionfindset;

import java.util.HashMap;

public class UnionFindSet<T> {
	/* Keeps track of the parent node */
	private HashMap<T, T> parent = new HashMap<>();
	/* Stores the depth of trees (rank) */
	private HashMap<T, Integer> rank = new HashMap<>();

	/* MakeSet operation */
	public void makeSet(T element) throws UnionFindSetException {
		if (element == null)
			throw new UnionFindSetException("makeSet method: element parameter cannot be null");
		if (parent.get(element) != null)
			return;
		parent.put(element, element);
		rank.put(element, 0);
	}

	/* It implements path compression */
	public T find(T element) throws UnionFindSetException {
		if (element == null)
			throw new UnionFindSetException("find method: element parameter cannot be null");
		if (parent.get(element) != element) {
			parent.put(element, find(parent.get(element)));
		}
		return parent.get(element);
	}

	/* Union of two sets into one set */
	public void union(T element1, T element2) throws UnionFindSetException {
		if (element1 == null || element2 == null)
			throw new UnionFindSetException("union method: element parameter cannot be null");
		T el1 = find(element1);
		T el2 = find(element2);
		if (el1 == el2)
			return;
		link(el1, el2);
	}

	/*
	 * It implements union by rank. Always attach a smaller depth tree under the root of the deeper
	 * tree.
	 */
	private void link(T element1, T element2) {
		if (rank.get(element1) > rank.get(element2))
			parent.put(element2, element1);
		else {
			parent.put(element1, element2);
			if ((rank.get(element1)).equals(rank.get(element2)))
				rank.put(element2, rank.get(element2) + 1);
		}
	}
}
