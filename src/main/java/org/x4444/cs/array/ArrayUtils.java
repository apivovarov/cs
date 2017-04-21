package org.x4444.cs.array;

import java.util.*;

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

  public static int mostPopular(int[] a) {
    if (a == null || a.length == 0) {
      throw new RuntimeException("Empty array");
    }
    Map<Integer, Integer> m = new HashMap();
    for (int v : a) {
      Integer vv = Integer.valueOf(v);
      Integer cnt = m.get(vv);
      if (cnt == null) {
        cnt = 0;
      }
      cnt++;
      m.put(vv, cnt);
    }
    int cnt = 0;
    int mostPopular = 0;
    for(Map.Entry<Integer, Integer> entry : m.entrySet()) {
      if (entry.getValue() > cnt) {
        cnt = entry.getValue();
        mostPopular = entry.getKey();
      }
    }
    return mostPopular;
  }

  public static void rearrange(int[] a) {
    if (a == null || a.length <= 1) {
      return;
    }

    int b = 0;
    int e = a.length - 1;

    while (b < e) {
      int i = findLeftZero(a, b);
      int j = findRightNz(a, e);

      if (i == -1 || j == -1 || j < i) {
        return;
      }

      swap(a, i, j);
      b = i + 1;
      e = j - 1;
    }
  }

  static void swap(int[] a, int i, int j) {
    int buff = a[j];
    a[j] = a[i];
    a[i] = buff;
  }

  static int findLeftZero(int[] a, int b) {
    for(int i = b; i < a.length; i++) {
      if (a[i] == 0) {
        return i;
      }
    }
    return -1;
  }

  static int findRightNz(int[] a, int e) {
    for(int i = e; i >= 0; i--) {
      if (a[i] != 0) {
        return i;
      }
    }
    return -1;
  }
}
