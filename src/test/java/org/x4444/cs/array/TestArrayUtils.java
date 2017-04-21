package org.x4444.cs.array;

import org.junit.Assert;
import org.junit.Test;

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

  @Test
  public void testMostPopular() {
    try {
      ArrayUtils.mostPopular(null);
      Assert.fail("mostPopular should throw RuntimeException");
    } catch (RuntimeException e) {
      // ignore
    }

    try {
      ArrayUtils.mostPopular(new int[] {});
      Assert.fail("mostPopular should throw RuntimeException");
    } catch (RuntimeException e) {
      // ignore
    }

    int[] a = {1, 2, 3, 4, 5};
    int mostPopular = ArrayUtils.mostPopular(a);
    Assert.assertEquals(1, mostPopular);

    a = new int[] {1, 2, 3, 4, 5, 3};
    mostPopular = ArrayUtils.mostPopular(a);
    Assert.assertEquals(3, mostPopular);

    a = new int[] {4};
    mostPopular = ArrayUtils.mostPopular(a);
    Assert.assertEquals(4, mostPopular);
  }

  @Test
  public void testRearrange() {
    int[] a = new int[] {0, 2};
    ArrayUtils.rearrange(a);
    Assert.assertArrayEquals(new int[]{2, 0}, a);

    a = new int[] {2, 0};
    ArrayUtils.rearrange(a);
    Assert.assertArrayEquals(new int[]{2, 0}, a);

    a = new int[] {0, 5, 2};
    ArrayUtils.rearrange(a);
    Assert.assertArrayEquals(new int[]{2, 5, 0}, a);

    a = new int[] {0, 5, 0, 2};
    ArrayUtils.rearrange(a);
    Assert.assertArrayEquals(new int[]{2, 5, 0, 0}, a);

    a = new int[] {0, 0, 0, 0, 2};
    ArrayUtils.rearrange(a);
    Assert.assertArrayEquals(new int[]{2, 0, 0, 0, 0}, a);

    a = new int[] {0, 0, 0, 2, 1};
    ArrayUtils.rearrange(a);
    Assert.assertArrayEquals(new int[]{1, 2, 0, 0, 0}, a);

    a = new int[] {1, 2, 0, 0, 0};
    ArrayUtils.rearrange(a);
    Assert.assertArrayEquals(new int[]{1, 2, 0, 0, 0}, a);

    a = new int[] {4, 0, 0, 2, 0, 0, 0};
    ArrayUtils.rearrange(a);
    Assert.assertArrayEquals(new int[]{4, 2, 0, 0, 0, 0, 0}, a);
  }
}
