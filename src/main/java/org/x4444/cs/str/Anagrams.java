package org.x4444.cs.str;

import java.util.ArrayList;
import java.util.List;

/**
 * Anagrams
 */
public class Anagrams {

    public static final long DELIM = 10000000000L;

    /**
     * Find anagrams of b in string a
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

         /*
         String hash is calculated as sum of char hashes
         char hash is <char_value> * 10,000,000,000 + 1 (max str length is 2,147,483,647)
         e.g. ABC hash is
          650,000,000,001
        + 660,000,000,001
        + 670,000,000,001
        ------------------
        1,980,000,000,003
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
                     i
         i points to right side of window
         if window size is 3 it will contain window contain "bca"
         */
        for (int i = 1; i <= a.length() - b.length(); i++) {
            // add right most char to hash
            strHash = updateStrHash(strHash, a.charAt(i + b.length() - 1), true);

            // remove previous left most char from hash
            strHash = updateStrHash(strHash, a.charAt(i - 1), false);

            // compare hashes
            if (strHash == refSrtHash) {
                res.add(i);
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
        long strHash = 0L;
        for (int i = st; i < st + len; i++) {
            strHash = updateStrHash(strHash, s.charAt(i), true);
        }
        return strHash;
    }

    protected long updateStrHash(long strHash, char ch, boolean isAdd) {
        long diff = ch * DELIM + 1L;
        return isAdd ? strHash + diff : strHash - diff;
    }
}
