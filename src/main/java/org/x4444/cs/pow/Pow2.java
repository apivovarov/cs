package org.x4444.cs.pow;

public class Pow2 {

    public static boolean isPow2(int n) {
        return n == 0 ? false : (n & 1) == 1 ? n == 1 : isPow2(n >> 1);
    }
}
