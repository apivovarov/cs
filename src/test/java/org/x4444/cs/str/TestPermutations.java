package org.x4444.cs.str;

import org.junit.Assert;
import org.junit.Test;

import java.util.Arrays;
import java.util.HashSet;
import java.util.List;

/**
 * TestPermutations
 */
public class TestPermutations {

    @Test public void testFind() {
        Permutations p = new Permutations();
        Assert.assertTrue(eq(p.find("", ""), new IntPair[] {}));
        Assert.assertTrue(eq(p.find("abc", "abc"), new IntPair[] { new IntPair(0, 2) }));
        Assert.assertTrue(eq(p.find("qmcabt", "abc"), new IntPair[] { new IntPair(2, 4) }));
        Assert.assertTrue(eq(p.find("abca", "bac"), new IntPair[] { new IntPair(0, 2), new IntPair(1, 3) }));
        Assert.assertTrue(eq(p.find("abc_abc", "abc"), new IntPair[] { new IntPair(0, 2), new IntPair(4, 6) }));
    }

    boolean eq(List<IntPair> a, IntPair[] b) {
        return a.size() == b.length && (new HashSet<IntPair>(a)).containsAll(new HashSet<IntPair>(Arrays.asList(b)));
    }
}
