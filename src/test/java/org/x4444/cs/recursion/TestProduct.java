package org.x4444.cs.recursion;

import java.util.Arrays;
import java.util.List;

import org.junit.Assert;

import org.junit.Test;

public class TestProduct {

  @Test
  public void testGetProduct() {
    List<Integer> a = Arrays.asList(1, 2, 3);
    List<Integer> b = Arrays.asList(4, 5);
    List<Integer> c = Arrays.asList(6, 7, 8);
    List<List<Integer>> input = Arrays.asList(a, b, c);
    List<int[]> product = Product.getProduct(input);

    StringBuilder sb = new StringBuilder();
    for (int[] arr : product) {
      if (sb.length() > 0) {
        sb.append(",");
      }
      sb.append(Arrays.toString(arr));
    }

    Assert
        .assertEquals(
            "[1, 4, 6],[1, 4, 7],[1, 4, 8],[1, 5, 6],[1, 5, 7],[1, 5, 8],[2, 4, 6],[2, 4, 7],[2, 4, 8],[2, 5, 6],[2, 5, 7],[2, 5, 8],[3, 4, 6],[3, 4, 7],[3, 4, 8],[3, 5, 6],[3, 5, 7],[3, 5, 8]",
            sb.toString());
  }
}
