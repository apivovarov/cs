package org.x4444.cs.matrix;

/**
 * MatrixRotate
 */
public class MatrixRotate {

    public void rotate(int[][] m) {
        int h = m.length;
        if (h < 1) {
            return;
        }
        int w = m[0].length;
        assert w == h;
        if (h == 1) {
            return;
        }

        for (int i = 0; i < w / 2; i++) {
            int start = i;
            int stop = w - i - 1;
            int size = stop - start + 1;
            for (int j = 0; j < size - 1; j++) {
                int b = m[start][start];
                shiftCol(m, start, start, stop, true);
                shiftRow(m, stop, start, stop, false);
                shiftCol(m, stop, start, stop, false);
                shiftRow(m, start, start + 1, stop, true);
                m[start][start + 1] = b;
            }
        }
    }

    void shiftRow(int[][] m, int y, int x1, int x2, boolean isRight) {
        int[] row = m[y];

        if (isRight) {
            int src = x2;
            while (--src >= x1) {
                row[src + 1] = row[src];
            }
        } else {
            int src = x1;
            while (++src <= x2) {
                row[src - 1] = row[src];
            }
        }
    }

    void shiftCol(int[][] m, int x, int y1, int y2, boolean isUp) {
        if (isUp) {
            int src = y1;
            while (++src <= y2) {
                m[src - 1][x] = m[src][x];
            }
        } else {
            int src = y2;
            while (--src >= y1) {
                m[src + 1][x] = m[src][x];
            }
        }
    }
}
