package org.x4444.cs.array;

import org.junit.Assert;
import org.junit.Test;
import org.x4444.cs.array.ArrayUtils;

public class TestArrayUtils {

  @Test
  public void testIntersect() {
    int[] a = { 1, 2, 6, 7, 8, 6, 2 };
    int[] b = { 4, 2, 2, 2, 7, 6, 9, 5 };
    int[] c = ArrayUtils.intersect(a, b);
    Assert.assertArrayEquals(new int[] { 2, 2, 6, 7 }, c);
  }

  @Test
  public void testIntersectForSmallArrOrNull() {
    int[] a = { 2 };
    int[] b = { 2, 4 };
    int[] c = ArrayUtils.intersect(a, b);
    Assert.assertArrayEquals(new int[] { 2 }, c);

    a = new int[] { 2 };
    b = new int[] { 2 };
    c = ArrayUtils.intersect(a, b);
    Assert.assertArrayEquals(new int[] { 2 }, c);

    a = new int[0];
    b = new int[] { 2 };
    c = ArrayUtils.intersect(a, b);
    Assert.assertArrayEquals(new int[0], c);

    a = new int[] { 2 };
    b = new int[0];
    c = ArrayUtils.intersect(a, b);
    Assert.assertArrayEquals(new int[0], c);

    a = null;
    b = new int[] { 2 };
    c = ArrayUtils.intersect(a, b);
    Assert.assertNull(c);

    a = new int[] { 2 };
    b = null;
    c = ArrayUtils.intersect(a, b);
    Assert.assertNull(c);
  }
}
