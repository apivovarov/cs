package org.x4444.cs.sort;

/**
 * BubbleSort
 */
public class BubbleSort {

    public static void sort(int[] arr) {
        int end = arr.length;
        while (end > 1) {
            for (int i = 1; i < end; i++) {
                if (arr[i - 1] > arr[i]) {
                    int b = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = b;
                }
            }
            end--;
        }
    }
}
