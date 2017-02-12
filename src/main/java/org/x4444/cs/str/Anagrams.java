package org.x4444.cs.str;

import java.util.ArrayList;
import java.util.List;

/**
 * Anagrams
 */
public class Anagrams {
    // 30 prime numbers
    private int[] PRIMES =
        new int[] {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
            79, 83, 89, 97, 101, 103, 107, 109, 113};

    /**
     * Find anagrams of b in string a
     * Case insensitive
     *
     * @param a - String where to find anagrams of b
     * @param b - Source of anagrams
     * @return array containing start positions of the anagrams or empty array if nothing is found
     */
    public int[] find(String a, String b) {
        List<Integer> res = new ArrayList<Integer>();
        if (a == null || a.isEmpty() || b == null || b.isEmpty() || b.length() > a.length()) {
            return new int[0];
        }
        assert a.matches("^[a-zA-Z]*$");
        assert b.matches("^[a-zA-Z]*$");
         /*
         We can use Fundamental theorem of arithmetic to calculate String hash code
         https://en.wikipedia.org/wiki/Fundamental_theorem_of_arithmetic

         String chars are converted to corresponding prime numbers
         A - 2
         B - 3
         C - 5
         D - 7

         String hash is calculated as product of all chars prime numbers

         e.g. ABC hash is 2 * 3 * 5 = 30. No other string can have hash code 30.
         */

        long refSrtHash = getStrHash(b, 0, b.length());
        long strHash = getStrHash(a, 0, b.length());
        // compare hashes
        if (strHash == refSrtHash) {
            res.add(0);
        }

        /*
         string a - abcabc
                     ^ ^
                       rightId
         rightId points to right side of the window
         e.g. if window size is 3 and rightId = 3 then the window will contain "bca"
         */
        for (int rightId = b.length(); rightId < a.length(); rightId++) {
            // add right most char to hash
            strHash = updateStrHash(strHash, a.charAt(rightId), true);

            // remove previous left most char from hash
            int prevLeftId = rightId - b.length();
            strHash = updateStrHash(strHash, a.charAt(prevLeftId), false);

            // compare hashes and add leftId to resulting List
            if (strHash == refSrtHash) {
                res.add(prevLeftId + 1);
            }
        }

        // copy results to int[]
        int[] resArr = new int[res.size()];
        for (int i = 0; i < res.size(); i++) {
            resArr[i] = res.get(i);
        }
        return resArr;
    }

    protected long getStrHash(String s, int st, int len) {
        long strHash = 1L;
        for (int i = st; i < st + len; i++) {
            strHash = updateStrHash(strHash, s.charAt(i), true);
        }
        return strHash;
    }

    protected long updateStrHash(long strHash, char ch, boolean isAdd) {
        int id;
        if (ch >= 97 && ch <= 122) {
            // get lowercase chars a-z prime number id
            id = ch - 32 - 65;
        } else {
            // get uppercase chars A-Z prime number id
            id = ch - 65;
        }
        long prime = PRIMES[id];
        return isAdd ? strHash * prime : strHash / prime;
    }
}
