package org.x4444.cs.comb;

import org.junit.Assert;
import org.junit.Test;

import java.util.Collection;

public class TestItemComb {

    @Test
    public void testGetComb() {
        Collection<String> set = ItemComb.getComb("abc");
        Assert.assertEquals(7, set.size());
        Assert.assertTrue(set.contains("abc"));
        Assert.assertTrue(set.contains("a"));
        Assert.assertTrue(set.contains("b"));
        Assert.assertTrue(set.contains("c"));
        Assert.assertTrue(set.contains("ab"));
        Assert.assertTrue(set.contains("ac"));
        Assert.assertTrue(set.contains("bc"));

        set = ItemComb.getComb("abcde");
        Assert.assertEquals(31, set.size());
        Assert.assertTrue(set.contains("abcde"));
        Assert.assertTrue(set.contains("a"));
        Assert.assertTrue(set.contains("b"));
        Assert.assertTrue(set.contains("d"));
        Assert.assertTrue(set.contains("ace"));
        Assert.assertTrue(set.contains("ce"));
        Assert.assertTrue(set.contains("bd"));
        Assert.assertTrue(set.contains("abde"));

        // null or empty string
        set = StringSubSeq.getAllSubSeq(null);
        Assert.assertNull(set);
        set = StringSubSeq.getAllSubSeq("");
        Assert.assertNull(set);

        // long string
        try {
            set = StringSubSeq.getAllSubSeq("12345678901234567890123456789012");
            Assert.assertTrue("Exception is expected", false);
        } catch (IllegalArgumentException e) {
            Assert.assertEquals("max str length is 31", e.getMessage());
        }

        set = StringSubSeq.getAllSubSeq("1234567890abcdef");
        Assert.assertEquals(65535, set.size());
    }
}
