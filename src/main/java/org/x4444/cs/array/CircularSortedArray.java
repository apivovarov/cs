package org.x4444.cs.array;

import java.util.Arrays;

public class CircularSortedArray {

  /**
   * Searches for specified int value using the binary search algorithm.<br>
   * Array must be circular sorted, e.g. [10,11,12,13,1,3,7,9]
   *
   * @param a
   *          circular sorted int array.
   * @param num
   *          int value.
   * @return index of num in the array a or -1 if not found.<br>
   *         Example: binarySearch([10,11,12,13,1,3,7,9], 3) = 5
   */
  public static int binarySearch(int[] a, int num) {
    if (a == null) {
      return -1;
    }
    if (a.length == 1) {
      return a[0] == num ? 0 : -1;
    }

    int leftIdx = 0;
    int rightIdx = a.length - 1;

    while (leftIdx >= 0 && rightIdx >= 0 && leftIdx != rightIdx) {
      int midIdx = leftIdx + (rightIdx - leftIdx) / 2;
      int midV = a[midIdx];
      int leftV = a[leftIdx];
      int rightV = a[rightIdx];
      if (leftV == num) {
        return leftIdx;
      }
      if (midV == num) {
        return midIdx;
      }
      if (rightV == num) {
        return rightIdx;
      }

      // left is sorted
      if (leftV < midV) {
        if (num > leftV && num < midV) {
          // num is in left-mid sorted range
          int resIdx = Arrays.binarySearch(a, leftIdx, midIdx, num);
          return resIdx < 0 ? -1 : resIdx;
        }
        // 10-12 look for 3
        // change leftIdx and midIdx and try again
        leftIdx = midIdx + 1;
      } else {
        // right is sorted
        if (num > midV && num < rightV) {
          // num is in mid-right sorted range
          int resIdx = Arrays.binarySearch(a, midIdx, rightIdx, num);
          return resIdx < 0 ? -1 : resIdx;
        }
        // 1-9 look for 12
        // change rightIdx and midIdx and try again
        rightIdx = midIdx - 1;
      }
    }
    return -1;
  }
}
