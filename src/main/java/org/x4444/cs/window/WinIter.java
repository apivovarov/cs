package org.x4444.cs.window;

import java.util.TreeSet;

public class WinIter {

  /**
   * Example: max([-1, 3, 1, 10, 7, 9, -2, 4], 3) = [3, 10, 10, 10, 9, 9]
   *
   * @param a - input array of integers
   * @param winSize - size of the sliding window
   * @return new Array containing max values from sliding window
   */
  public static int[] max(int[] a, int winSize) {
    if (a == null || a.length == 0) {
      return a;
    }
    if (a.length < winSize) {
      winSize = a.length;
    }

    TreeSet<Integer> tree = new TreeSet<Integer>();
    int maxI = a.length - winSize + 1;
    int[] out = new int[maxI];
    for (int i = 0; i < winSize; i++) {
      tree.add(a[i]);
    }
    out[0] = tree.last();

    for (int i = winSize; i < a.length; i++) {
      int prevWinFirstIdx = i - winSize;
      tree.remove(a[prevWinFirstIdx]);
      tree.add(a[i]);
      int outIdx = i - winSize + 1;
      out[outIdx] = tree.last();
    }
    return out;
  }
}
