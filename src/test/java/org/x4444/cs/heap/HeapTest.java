package org.x4444.cs.heap;

import org.junit.Assert;
import org.junit.Test;

import java.util.Arrays;

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

        Assert.assertEquals(8, h.size());
        Assert.assertEquals(46, h.max());
        Assert.assertEquals(46, h.removeMax());
        Assert.assertEquals(7, h.size());
        Assert.assertEquals(26, h.max());
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

        Assert.assertEquals(8, h.size());
        Assert.assertEquals(12, h.capacity());
    }
}
