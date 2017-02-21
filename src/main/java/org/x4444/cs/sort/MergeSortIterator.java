package org.x4444.cs.sort;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.TreeMap;

/**
 * MergeSortIterator
 */
public class MergeSortIterator implements Iterator<Integer> {

    TreeMap<KI, Iterator<Integer>> tree = new TreeMap<KI, Iterator<Integer>>();

    List<Integer> list = new ArrayList<Integer>();

    List<Iterator<Integer>> iters;

    public MergeSortIterator(List<Iterator<Integer>> iters) {
        this.iters = iters;
        // init tree
        for (int i = 0; i < iters.size(); i++) {
            Iterator<Integer> iter = iters.get(i);
            if (iter.hasNext()) {
                tree.put(new KI(iter.next(), i), iter);
            }
        }
    }

    @Override
    public boolean hasNext() {
        return !tree.isEmpty();
    }

    @Override
    public Integer next() {
        if (!hasNext()) {
            throw new NoSuchElementException();
        }
        KI ki = tree.firstKey();
        Integer v = ki.v;
        Iterator<Integer> kIter = tree.remove(ki);
        if (kIter.hasNext()) {
            ki.v = kIter.next();
            tree.put(ki, kIter);
        }
        return v;
    }

    static class KI implements Serializable, Comparable<KI> {
        Integer v;
        int id;

        public KI() {

        }

        public KI(Integer v, int id) {
            this.v = v;
            this.id = id;
        }

        @Override
        public int compareTo(KI o) {
            int res = v.compareTo(o.v);
            if (res != 0) {
                return res;
            }
            return id - o.id;
        }
    }
}
