package org.x4444.cs.sort;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeMap;

/**
 * MergeSort
 */
public class MergeSort {

    public static List<Integer> sort(List<Iterator<Integer>> iters) {

        TreeMap<KI, Iterator<Integer>> tree = new TreeMap<KI, Iterator<Integer>>();

        List<Integer> list = new ArrayList<Integer>();

        // init tree
        for (int i = 0; i < iters.size(); i++) {
            Iterator<Integer> iter = iters.get(i);
            if (iter.hasNext()) {
                tree.put(new KI(iter.next(), i), iter);
            }
        }

        while (!tree.isEmpty()) {
            KI ki = tree.firstKey();
            Integer v = ki.v;
            int id = ki.id;
            Iterator<Integer> kIter = tree.remove(ki);
            if (kIter.hasNext()) {
                ki.v = kIter.next();
                tree.put(ki, kIter);
            }
            list.add(v);
        }

        return list;
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
