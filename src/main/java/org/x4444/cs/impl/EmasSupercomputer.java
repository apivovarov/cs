package org.x4444.cs.impl;

import java.io.InputStream;
import java.util.Scanner;

public class EmasSupercomputer {

    static int n;
    static int m;
    static boolean[][] mx;

    static void init(InputStream is) {
        Scanner s = new Scanner(is);
        n = s.nextInt();
        m = s.nextInt();
        mx = new boolean[n][m];
        for (int i = 0; i < n; i++) {
            mx[i] = strToBA(s.next());
        }
    }

    static void print() {
        System.out.print("  ");
        for (int j = 0; j < m; j++) {
            System.out.print(j + " ");
        }
        System.out.println();
        for (int i = 0; i < n; i++) {
            System.out.print(i + " ");
            for (int j = 0; j < m; j++) {
                System.out.print(mx[i][j] ? "1 " : "0 ");
            }
            System.out.println();
        }
    }

    static boolean[] strToBA(String s) {
        boolean[] arr = new boolean[s.length()];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = 'G' == s.charAt(i) || 'g' == s.charAt(i);
        }
        return arr;
    }

    static int[] findNext(int x, int y) {
        while (true) {
            if (x == m) {
                x = 0;
                y += 1;
            }
            if (y == n) {
                return null;
            }

            if (mx[y][x]) {
                return new int[]{x, y};
            }
            x++;
        }
    }

    static int fill(int x, int y, int size) {
        if (y - size < 0 || y + size > n - 1 || x - size < 0 || x + size > m - 1) {
            return -1;
        }
        int i = size;

        if (!mx[y - i][x] || !mx[y][x + i] || !mx[y + i][x] || !mx[y][x - i]) {
            return -1;
        }

        mx[y - i][x] = false;
        mx[y][x + i] = false;
        mx[y + i][x] = false;
        mx[y][x - i] = false;

        return size;
    }

    static void unFill(int x, int y, int size) {
        if (size == -1) {
            return;
        }
        for (int i = 0; i <= size; i++) {
            mx[y - i][x] = true;
            mx[y][x + i] = true;
            mx[y + i][x] = true;
            mx[y][x - i] = true;
        }
    }

    static int findMaxSq() {
        int[] cc = {-1, 0};
        int sq = 0;
        while (true) {
            cc = findNext(cc[0] + 1, cc[1]);
            if (cc == null) {
                break;
            }
            // System.out.println(cc[0] + ", " + cc[1]);
            for (int sz = 0; sz < 16; sz++) {
                int fill = fill(cc[0], cc[1], sz);
                if (fill == -1) {
                    unFill(cc[0], cc[1], sz - 1);
                    break;
                }
                int sq1 = fill * 4 + 1;
                int[] cc2 = cc;
                while (true) {
                    cc2 = findNext(cc2[0] + 1, cc2[1]);
                    if (cc2 == null) {
                        break;
                    }
                    for (int sz2 = 0; sz2 < 16; sz2++) {
                        int fill2 = fill(cc2[0], cc2[1], sz2);
                        if (fill2 == -1) {
                            unFill(cc2[0], cc2[1], sz2 - 1);
                            break;
                        }
                        int sq2 = fill2 * 4 + 1;
                        int sqN = sq1 * sq2;
                        if (sqN > sq) {
                            sq = sqN;
                        }
                    }
                }
            }
        }
        return sq;
    }
}
