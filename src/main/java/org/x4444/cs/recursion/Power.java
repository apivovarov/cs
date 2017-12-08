package org.x4444.cs.recursion;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

public class Power {

    static void add(int num, int n, Set<Integer> used, Set all) {
        if (num == 0 ) {
            if (!all.contains(used)) {
                all.add(used.toString());
            }
            return;
        }
        int root = (int) Math.pow(num, 1.0/n);
        //System.out.println("num: " + num + "; n:" + n + "; root: " + root);
        if (root >= 1) {
            int min = root / 2;
            if (min <= 0) {
                min = 1;
            }
            for (int e = root; e >= min; e--) {
                if (used.contains(e)) {
                    continue;
                }
                used.add(e);
                //System.out.println(used);
                int num2 = num - (int) Math.pow(e, n);
                add(num2, n, used, all);
                used.remove(e);
            }
        }
    }

    public static void main(String[] args) {
        int x = 800;
        int n = 2;
        HashSet all = new HashSet();

        add(x, n, new HashSet(), all);
        System.out.println(all.size());
        for (Object o : all) {
            // System.out.println(o);
        }
    }
}
