package org.x4444.cs.matrix;

import org.junit.Assert;
import org.junit.Test;

/**
 * TestMatrixRotate
 */
public class TestMatrixRotate {

    @Test
    public void testRotate4() {
        int[][] m = new int[][] {
            new int[] {1, 2, 3, 4},
            new int[] {5, 6, 7, 8},
            new int[] {9, 10, 11, 12},
            new int[] {13, 14, 15, 16}
        };

        int[][] resM = new int[][] {
            new int[] {13, 9, 5, 1},
            new int[] {14, 10, 6, 2},
            new int[] {15, 11, 7, 3},
            new int[] {16, 12, 8, 4}
        };

        MatrixRotate mr = new MatrixRotate();
        mr.rotate(m);
        printMatrix(m);

        Assert.assertArrayEquals(resM, m);
    }

    @Test
    public void testRotate5() {
        int[][] m = new int[][] {
            new int[] {10, 11, 12, 13, 14},
            new int[] {20, 21, 22, 23, 24},
            new int[] {30, 31, 32, 33, 34},
            new int[] {40, 41, 42, 43, 44},
            new int[] {50, 51, 52, 53, 54}
        };

        int[][] resM = new int[][] {
            new int[] {50, 40, 30, 20, 10},
            new int[] {51, 41, 31, 21, 11},
            new int[] {52, 42, 32, 22, 12},
            new int[] {53, 43, 33, 23, 13},
            new int[] {54, 44, 34, 24, 14}
        };

        MatrixRotate mr = new MatrixRotate();
        mr.rotate(m);
        printMatrix(m);

        Assert.assertArrayEquals(resM, m);
    }

    void printMatrix(int [][] m) {
        System.out.println("-------------------------------------------");
        for (int[] r : m) {
            for (int v : r) {
                System.out.print(v);
                System.out.print("\t");
            }
            System.out.println();
        }
        System.out.println("-------------------------------------------");
    }
}
