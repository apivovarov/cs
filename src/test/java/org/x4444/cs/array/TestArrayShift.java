package org.x4444.cs.array;

import org.junit.Assert;
import org.junit.Test;
import org.x4444.cs.array.ArrayShift;

public class TestArrayShift {
  @Test
  public void testShiftLeft() {
    int[] a = { 8, 9, 1, 2, 3, 4, 5, 6, 7 };
    ArrayShift.shiftLeft(a, 2);
    int[] exp = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    Assert.assertArrayEquals(exp, a);
  }

  @Test
  public void testShiftLeftForBoundaryConditions() {
    int[] a = null;
    ArrayShift.shiftLeft(a, 2);
    Assert.assertEquals(a, a);

    a = new int[0];
    ArrayShift.shiftLeft(a, 2);
    Assert.assertEquals(a, a);

    a = new int[] { 8, 9, 1, 2, 3, 4, 5, 6, 7 };
    ArrayShift.shiftLeft(a, 0);
    Assert.assertArrayEquals(a, a);

    ArrayShift.shiftLeft(a, -1);
    Assert.assertArrayEquals(a, a);

    ArrayShift.shiftLeft(a, a.length);
    Assert.assertArrayEquals(a, a);

    ArrayShift.shiftLeft(a, a.length + 2);
    int[] exp = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    Assert.assertArrayEquals(exp, a);
  }
}
