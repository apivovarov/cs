package org.x4444.cs.lcs;

/**
 * LCS
 */
public class LCS {

    String s1, s2;

    public LCS(String s1, String s2) {
        this.s1 = s1;
        this.s2 = s2;
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
        if (s1.charAt(i1) == s2.charAt(i2)) {
            return 1 + getLen(i1 + 1, i2 + 1);
        }
        return Math.max(getLen(i1, i2 + 1), getLen(i1 + 1, i2));
    }
}
