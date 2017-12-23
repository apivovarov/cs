package org.x4444.cs.lcs;

import static java.lang.Math.max;

/**
 * LCS
 */
public class LCSInt {

    int[] a1, a2;

    int[][] mx;

    public LCSInt(int[] s1, int[] s2) {
        this.a1 = s1;
        this.a2 = s2;
        this.mx = new int[s1.length + 1][s2.length + 1];
    }

    void fillMatrix() {
        for (int i = 1; i <= a1.length; i++) {
            for (int j = 1; j <= a2.length; j++) {
                if (a1[i - 1] == a2[j - 1]) {
                    mx[i][j] = mx[i - 1][j - 1] + 1;
                } else {
                    mx[i][j] = max(mx[i - 1][j], mx[i][j - 1]);
                }
            }
        }
    }

    void printMatrix() {
        for (int i = 0; i <= a1.length; i++) {
            for (int j = 0; j <= a2.length; j++) {
                System.out.print(mx[i][j] + " ");
            }
            System.out.println();
        }
    }

    int[] walkMatrix() {
        int i = a1.length;
        int j = a2.length;
        int v = mx[i][j];
        int[] chArr = new int[v];
        walkMatrixInt(i, j, chArr);
        return chArr;
    }

    void walkMatrixInt(int i, int j, int[] chArr) {
        int v = mx[i][j];
        if (v == 0) {
            return;
        }
        if (mx[i - 1][j] < v && mx[i][j - 1] < v) {
            chArr[v - 1] = a1[i - 1];
            walkMatrixInt(i - 1, j - 1, chArr);
        } else {
            if (mx[i][j - 1] == v) {
                walkMatrixInt(i, j - 1, chArr);
            } else {
                walkMatrixInt(i - 1, j, chArr);
            }
        }
    }

    public int[] findLcs() {
        fillMatrix();
        int[] res = walkMatrix();
        return res;
    }
}
