package org.x4444.cs.array;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ArrayUtils {
  /**
   * Calculates int arrays intersect
   * 
   * @param a
   *          int array
   * @param b
   *          int array
   * @return intersect array or null if a or b is null
   */
  public static int[] intersect(int[] a, int[] b) {
    if (a == null || b == null) {
      return null;
    }
    if (a.length == 0 || b.length == 0) {
      return new int[0];
    }

    Arrays.sort(a);
    Arrays.sort(b);

    int aPos = 0;
    int bPos = 0;

    List<Integer> res = new ArrayList<Integer>();
    while (aPos < a.length && bPos < b.length) {
      int aV = a[aPos];
      int bV = b[bPos];
      if (aV == bV) {
        res.add(aV);
        aPos++;
        bPos++;
      } else if (aV < bV) {
        aPos++;
      } else {
        bPos++;
      }
    }
    int[] resArr = new int[res.size()];
    for (int i = 0; i < res.size(); i++) {
      resArr[i] = res.get(i).intValue();
    }
    return resArr;
  }
}
