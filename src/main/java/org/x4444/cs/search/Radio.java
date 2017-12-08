package org.x4444.cs.search;

import java.util.Scanner;

public class Radio {

    static int cover(boolean[] ar, int i, int k, int max) {
        int tI = i + k;
        if (tI >= max) {
            return max + k;
        }
        return getHome(ar, tI, false) + k;
    }

    static int getHome(boolean[] ar, int i, boolean fwd) {
        while (!ar[i]) {
            if (fwd) {
                i++;
            } else {
                i--;
            }
        }
        return i;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int k = in.nextInt();
        int[] x = new int[n];
        int max = 0;
        int min = Integer.MAX_VALUE;
        for (int x_i = 0; x_i < n; x_i++) {
            int v = in.nextInt();
            x[x_i] = v;
            if (v > max) {
                max = v;
            }
            if (v < min) {
                min = v;
            }
        }
        boolean[] ar = new boolean[max + 1];
        for (int v : x) {
            ar[v] = true;
        }

        int stop = min - 1;
        int cnt = 0;
        while (stop < max) {
            int start = getHome(ar, stop + 1, true);
            stop = cover(ar, start, k, max);
            cnt++;
        }
        System.out.println(cnt);
    }
}
