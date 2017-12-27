package org.x4444.cs.heap;

import org.junit.Assert;
import org.junit.Test;

import java.util.Arrays;
import java.util.Random;

public class HeapTest {

    @Test
    public void testAdd() {
        Heap h = new Heap(20);
        h.add(6);
        h.add(1);
        h.add(16);
        h.add(4);
        h.add(26);
        h.add(8);
        h.add(46);
        h.add(6);

        h.build();

        h.print();

        Assert.assertEquals(8, h.size());
        Assert.assertEquals(46, h.max());
        Assert.assertEquals(46, h.removeMax());
        Assert.assertEquals(7, h.size());
        Assert.assertEquals(26, h.max());
    }

    @Test
    public void testBuildAndSort() {
        Random r = new Random();
        int cap = 3001;
        Heap h = new Heap(cap);
        for (int i = 1; i <= cap; i++) {
            h.add(r.nextInt(1000000));
        }
        h.build();

        for (int i = 1; i <= cap / 2; i++) {
            Assert.assertTrue(h.getArr()[i] >= h.getArr()[i * 2]);
            Assert.assertTrue(h.getArr()[i] >= h.getArr()[i * 2 + 1]);
        }

        h.sort();
        for (int i = 2; i <= cap; i++) {
            Assert.assertTrue(h.getArr()[i] >= h.getArr()[i - 1]);
        }
    }

    @Test
    public void testSort() {
        Heap h = new Heap(20);
        h.add(6);
        h.add(1);
        h.add(16);
        h.add(4);
        h.add(26);
        h.add(8);
        h.add(46);
        h.add(6);

        h.build();

        int size = h.size();

        Assert.assertEquals(8, h.size());
        h.sort();
        Assert.assertEquals(0, h.size());
        h.print();
        Assert.assertEquals("[1, 4, 6, 6, 8, 16, 26, 46]", Arrays.toString(Arrays.copyOfRange(h.getArr(), 1, size + 1)));
    }

    @Test
    public void testCapacity() {
        Heap h = new Heap(3);
        h.add(6);
        h.add(1);
        h.add(16);
        h.add(4);
        h.add(26);
        h.add(8);
        h.add(46);
        h.add(6);

        h.build();

        Assert.assertEquals(8, h.size());
        Assert.assertEquals(12, h.capacity());
    }
}
