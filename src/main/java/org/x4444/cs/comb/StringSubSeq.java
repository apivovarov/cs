package org.x4444.cs.comb;

import java.util.HashSet;
import java.util.Set;

/**
 * Brute force implementation for longest subsequence problem
 * 
 */
public class StringSubSeq {

  /**
   * Calculates all subsequences for given string
   * 
   * @param s
   * @return Set of subsequence strings or null
   */
  public static Set<String> getAllSubSeq(String s) {
    if (s == null || s.isEmpty()) {
      return null;
    }

    int n = s.length();
    if (n > 31) {
      throw new IllegalArgumentException("max str length is 31");
    }
    int total = (int) Math.pow(2, n) - 1;
    Set<String> set = new HashSet<String>(total);

    boolean[] mask = new boolean[n];
    set.add(s);

    // let get all other combinations except of "all false and all true" masks
    for (int i = 1; i < total; i++) {
      nextMask(mask);
      String subSeq = getSubseq(s, mask);
      set.add(subSeq);
    }
    return set;
  }

  public static void nextMask(boolean[] mask) {
    int p = mask.length - 1;
    while (p >= 0) {
      if (mask[p]) {
        mask[p] = false;
      } else {
        mask[p] = true;
        break;
      }
      p--;
    }
  }

  public static String getSubseq(String s, boolean[] mask) {
    if (s.length() != mask.length) {
      throw new IllegalArgumentException("str and mask have diff lenght");
    }
    StringBuilder sb = new StringBuilder();
    for (int i = 0; i < mask.length; i++) {
      if (mask[i]) {
        continue;
      }
      sb.append(s.charAt(i));
    }
    return sb.toString();
  }

  /**
   * Calculates the longest subsequence btw s1 and s2
   * 
   * @param s1
   * @param s2
   * @return the longest subsequence btw s1 and s2 or null if subsequence is not
   *         found
   */
  public static String getLongestSubSeq(String s1, String s2) {
    if (s1 == null || s2 == null) {
      return null;
    }
    Set<String> set1 = getAllSubSeq(s1);
    Set<String> set2 = getAllSubSeq(s2);
    if (set1 == null || set2 == null || set1.size() == 0 || set2.size() == 0) {
      return null;
    }

    String longest = "";
    for (String s : set1) {
      if (s.length() > longest.length() && set2.contains(s)) {
        longest = s;
      }
    }

    return longest.length() > 0 ? longest : null;
  }
}
