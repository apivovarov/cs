package org.x4444.cs.array;

import org.junit.Assert;
import org.junit.Test;
import org.x4444.cs.array.CircularSortedArray;

public class TestCircularSortedArray {

  @Test
  public void testbinarySearch() {
    int idx = CircularSortedArray.binarySearch(new int[] { 10, 11, 12, 13, 1, 3, 7, 9 }, 10);
    Assert.assertEquals(0, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 11, 12, 13, 1, 3, 7, 9 }, 11);
    Assert.assertEquals(1, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 11, 12, 13, 1, 3, 7, 9 }, 12);
    Assert.assertEquals(2, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 11, 12, 13, 1, 3, 7, 9 }, 13);
    Assert.assertEquals(3, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 11, 12, 13, 1, 3, 7, 9 }, 1);
    Assert.assertEquals(4, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 11, 12, 13, 1, 3, 7, 9 }, 3);
    Assert.assertEquals(5, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 11, 12, 13, 1, 3, 7, 9 }, 7);
    Assert.assertEquals(6, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 11, 12, 13, 1, 3, 7, 9 }, 9);
    Assert.assertEquals(7, idx);
  }

  @Test
  public void testbinarySearchForNullOrSmallArrays() {
    int idx = CircularSortedArray.binarySearch(null, 10);
    Assert.assertEquals(-1, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10 }, 10);
    Assert.assertEquals(0, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10 }, 0);
    Assert.assertEquals(-1, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 2 }, 0);
    Assert.assertEquals(-1, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 2 }, 2);
    Assert.assertEquals(1, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 2, 3 }, 2);
    Assert.assertEquals(1, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 11, 2, 3 }, 2);
    Assert.assertEquals(2, idx);

    idx = CircularSortedArray.binarySearch(new int[] { 10, 11, 2, 3 }, 11);
    Assert.assertEquals(1, idx);
  }
}
