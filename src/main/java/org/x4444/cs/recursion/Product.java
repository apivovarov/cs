package org.x4444.cs.recursion;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Product {

  public static List<int[]> getProduct(List<List<Integer>> input) {
    if (input == null) {
      return null;
    }
    List<int[]> product = new ArrayList<int[]>();
    int[] row = new int[input.size()];

    addProduct(input, 0, row, product);

    return product;
  }

  public static void addProduct(List<List<Integer>> input, int level, int[] row, List<int[]> product) {
    List<Integer> internalList = input.get(level);
    if (internalList == null) {
      return;
    }
    int nextLevel = level + 1;
    for (int v : internalList) {
      row = Arrays.copyOf(row, row.length);
      row[level] = v;
      // last level - print otherwise go deep
      if (nextLevel == input.size()) {
        product.add(row);
      } else {
        addProduct(input, nextLevel, row, product);
      }
    }
  }
}
