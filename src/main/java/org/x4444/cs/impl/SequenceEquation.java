package org.x4444.cs.impl;

public class SequenceEquation {

    public static void main(String[] args) {
        int n = 3;
        int[] ar = new int[n + 1];
        ar[1] = 2;
        ar[2] = 3;
        ar[3] = 1;

        int[] mp = new int[n + 1];

        for (int y = 1; y <= n; y++) {
            int x = ar[ar[y]];
            mp[x] = y;
        }
        for (int x = 1; x <= n; x++) {
            System.out.println(mp[x]);
        }
    }
}
