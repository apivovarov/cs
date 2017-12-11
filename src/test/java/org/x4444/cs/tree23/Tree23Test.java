package org.x4444.cs.tree23;

import org.junit.Assert;
import org.junit.Test;

public class Tree23Test {

    // values added to the tree
    int[] vv = new int[] { 50, 60, 70, 40, 30, 20, 10, 80, 90, 100 };
    // counts of elements less than vv[i] (after all elements are added)
    int[] ls2 = new int[] { 4, 5, 6, 3, 2, 1, 0, 7, 8, 9 };

    @Test
    public void testAdd() {
        // counts of elements less than vv[i] (while adding)
        int[] ls1 = new int[] { 0, 1, 2, 0, 0, 0, 0, 7, 8, 9 };

        Tree23 t = new Tree23();

        // 1st pass
        for (int i = 0; i < vv.length; i++) {
            int v = vv[i];
            int[] cArr = t.add(v);
            int lCnt = cArr[0];
            int vCnt = cArr[1];
            Assert.assertEquals(1, vCnt);
            Assert.assertEquals(ls1[i], lCnt);
        }
        Assert.assertEquals(vv.length, t.size());
        t.print();

        // 2nd pass
        for (int i = 0; i < vv.length; i++) {
            int v = vv[i];
            int[] cArr = t.add(v);
            int lCnt = cArr[0];
            int vCnt = cArr[1];
            Assert.assertEquals(2, vCnt);
            Assert.assertEquals(ls1[i] + ls2[i], lCnt);
        }
        Assert.assertEquals(vv.length * 2, t.size());

        Node23 n60 = t.find(60);
        Assert.assertTrue(n60.parent.elems[0].v == 40);
        Assert.assertTrue(n60.elems[0].v == 60 && n60.elems[1].v == 80 && n60.elems[2] == null);
        Assert.assertTrue(n60.children[0].elems[0].v == 50 && n60.children[1].elems[0].v == 70 && n60.children[2].elems[0].v == 90
            && n60.children[3] == null);
        Assert.assertTrue(!n60.isLeaf);
        Assert.assertEquals(12, n60.nCnt);
        Assert.assertEquals(vv.length * 2, t.root.nCnt);
    }

    @Test
    public void testGet() {
        Tree23 t = new Tree23();

        // 1st pass
        for (int v : vv) {
            t.add(v);
        }
        Assert.assertEquals(vv.length, t.size());
        t.print();
        for (int i = 0; i < vv.length; i++) {
            int v = vv[i];
            int[] cArr = t.get(v);
            int lCnt = cArr[0];
            int vCnt = cArr[1];
            Assert.assertEquals(1, vCnt);
            Assert.assertEquals(ls2[i], lCnt);
        }

        // 2nd pass
        for (int v : vv) {
            t.add(v);
        }
        Assert.assertEquals(vv.length * 2, t.size());
        for (int i = 0; i < vv.length; i++) {
            int v = vv[i];
            int[] cArr = t.get(v);
            int lCnt = cArr[0];
            int vCnt = cArr[1];
            Assert.assertEquals(2, vCnt);
            Assert.assertEquals(ls2[i] * 2, lCnt);
        }

        Assert.assertNull(t.get(999));
    }
}
