package org.x4444.cs.lcs;

/**
 * LCS
 */
public class LCS {

    String s1, s2;

    int[][] L;

    public LCS(String s1, String s2) {
        this.s1 = s1;
        this.s2 = s2;
        this.L = new int[s1.length() + 1][s2.length() + 1];
    }

    public int getLen() {
        if (s1.isEmpty() || s2.isEmpty()) {
            return 0;
        }
        return getLen(0, 0);
    }

    protected int getLen(int i1, int i2) {
        if (i1 >= s1.length() || i2 >= s2.length()) {
            return 0;
        }
        if (L[i1][i2] == 0) {
            if (s1.charAt(i1) == s2.charAt(i2)) {
                L[i1][i2] = 1 + getLen(i1 + 1, i2 + 1);
            } else {
                L[i1][i2] = Math.max(getLen(i1, i2 + 1), getLen(i1 + 1, i2));
            }
        }
        return L[i1][i2];
    }

    public int getLen2() {
        for (int i1 = s1.length() - 1; i1 >= 0; i1--) {
            for (int i2 = s2.length() - 1; i2 >= 0; i2--) {
                if (s1.charAt(i1) == s2.charAt(i2)) {
                    L[i1][i2] = 1 + L[i1 + 1][i2 + 1];
                } else {
                    L[i1][i2] = Math.max(L[i1][i2 + 1], L[i1 + 1][i2]);
                }
            }
        }
        return L[0][0];
    }

    public String getLcs() {
        int a[] = L[0];
        int prev = 0;
        StringBuilder lcs = new StringBuilder();
        for (int i = a.length - 1; i >= 0; i--) {
            if (a[i] != prev) {
                lcs.insert(0, s2.charAt(i));
                prev = a[i];
            }
        }
        return lcs.toString();
    }

    public void printL() {
        System.out.print("\t");
        for (int j = 0; j < s2.length(); j++) {
            System.out.print(s2.charAt(j));
            System.out.print("\t");
        }
        System.out.println("\n");

        for (int i = 0; i < s1.length(); i++) {
            System.out.print(s1.charAt(i));
            System.out.print("\t");
            for (int j = 0; j < s2.length(); j++) {
                System.out.print(L[i][j]);
                System.out.print("\t");
            }
            System.out.println("\n");
        }
        System.out.println("\n");
    }

}
