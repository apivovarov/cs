package org.x4444.cs.sort;

import org.junit.Assert;
import org.junit.Test;

/**
 * TestBubbleSort
 */
public class TestBubbleSort {

    @Test
    public void testSort() {
        int[] arr = {19, 1, 7, 2, 9, 15, -3};
        BubbleSort.sort(arr);
        int[] expArr = {-3, 1, 2, 7, 9, 15, 19};
        Assert.assertArrayEquals(expArr, arr);
    }
}
