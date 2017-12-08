package org.x4444.cs.tree23;

import org.junit.Assert;
import org.junit.Test;

public class Tree23Test {
    @Test
    public void testAdd() {
        int[] vv = new int[] { 50, 60, 70, 40, 30, 20, 10, 80, 90, 100 };
        Tree23 t = new Tree23();
        for (int v : vv) {
            t.add(v);
        }
        t.print();
        for (int v : vv) {
            Assert.assertEquals(Integer.valueOf(1), t.getCnt(v));
        }
        for (int v : vv) {
            t.add(v);
        }
        for (int v : vv) {
            Assert.assertEquals(Integer.valueOf(2), t.getCnt(v));
        }

        Node23 n60 = t.find(60);
        Assert.assertTrue(n60.parent.elems[0].v == 40);
        Assert.assertTrue(n60.elems[0].v == 60 && n60.elems[1].v == 80 && n60.elems[2] == null);
        Assert.assertTrue(n60.children[0].elems[0].v == 50 && n60.children[1].elems[0].v == 70 && n60.children[2].elems[0].v == 90
            && n60.children[3] == null);
        Assert.assertTrue(!n60.isLeaf);
    }
}
