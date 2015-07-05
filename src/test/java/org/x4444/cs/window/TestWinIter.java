package org.x4444.cs.window;

import org.junit.Assert;
import org.junit.Test;
import org.x4444.cs.window.WinIter;

public class TestWinIter {

  @Test
  public void testMax() {
    int[] a = { -1, 3, 1, 10, 7, 9, -2, 4 };
    int[] res = WinIter.max(a, 3);
    Assert.assertArrayEquals(new int[] { 3, 10, 10, 10, 9, 9 }, res);
  }

  @Test
  public void testMaxForSmallEmptyOrNullArray() {
    int[] a = { -1, 3 };
    int[] res = WinIter.max(a, 3);
    Assert.assertArrayEquals(new int[] { 3 }, res);

    a = new int[] { 2 };
    res = WinIter.max(a, 3);
    Assert.assertArrayEquals(new int[] { 2 }, res);

    a = new int[0];
    res = WinIter.max(a, 3);
    Assert.assertArrayEquals(a, res);

    a = null;
    res = WinIter.max(a, 3);
    Assert.assertNull(res);
  }
}
