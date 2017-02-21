package org.x4444.cs.sort;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.junit.Assert;
import org.junit.Test;

/**
 * TestMergeSortIterator
 */
public class TestMergeSortIterator {

    @Test
    public void testIterator() {
        int[] arr1 = {-3, 1, 2, 7, 9, 15, 19};
        int[] arr2 = {-6, 0, 3, 5, 10, 15, 19, 24};
        List<Iterator<Integer>> li = new ArrayList();

        li.add(getList(arr1).iterator());
        li.add(getList(arr2).iterator());

        Iterator<Integer> msIter = new MergeSortIterator(li);
        List<Integer> res = new ArrayList<Integer>();
        while (msIter.hasNext()) {
            res.add(msIter.next());
        }

        List<Integer> expRes = getList(new int[] {-6, -3, 0, 1, 2, 3, 5, 7, 9, 10, 15, 15, 19, 19, 24});
        Assert.assertEquals(expRes, res);
    }

    static List<Integer> getList(int[] arr) {
        List<Integer> li = new ArrayList();
        for (Integer a : arr) {
            li.add(a);
        }
        return li;
    }
}
