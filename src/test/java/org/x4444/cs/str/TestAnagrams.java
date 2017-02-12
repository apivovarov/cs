package org.x4444.cs.str;

import org.junit.Assert;
import org.junit.Test;

import java.util.Arrays;

/**
 * TestAnagrams
 */
public class TestAnagrams {

    @Test
    public void testFind() {
        Anagrams p = new Anagrams();
        int[] emptyArr = new int[0];
        Assert.assertTrue(eq(p.find("", ""), emptyArr));
        Assert.assertTrue(eq(p.find("abc", "abcd"), emptyArr));
        Assert.assertTrue(eq(p.find("abc", null), emptyArr));
        Assert.assertTrue(eq(p.find(null, "abcd"), emptyArr));
        Assert.assertTrue(eq(p.find("abc", "abc"), new int[] { 0 }));
        Assert.assertTrue(eq(p.find("qmcabt", "abc"), new int[] { 2 }));
        Assert.assertTrue(eq(p.find("abca", "bac"), new int[] { 0, 1 }));
        Assert.assertTrue(eq(p.find("abcZAbC", "abc"), new int[] { 0, 4 }));
    }

    /**
     * Arrays should be sorted
     *
     * @param a
     * @param b
     * @return
     */
    boolean eq(int[] a, int[] b) {
        return Arrays.equals(a, b);
    }
}
