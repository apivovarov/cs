package org.x4444.cs.comb;

import java.util.Set;

import org.junit.Assert;
import org.junit.Test;
import org.x4444.cs.comb.StringSubSeq;

public class TestStringSubSeq {

  @Test
  public void testGetAllSubSeq() {
    Set<String> set = StringSubSeq.getAllSubSeq("abc");
    Assert.assertEquals(7, set.size());
    Assert.assertTrue(set.contains("abc"));
    Assert.assertTrue(set.contains("a"));
    Assert.assertTrue(set.contains("b"));
    Assert.assertTrue(set.contains("c"));
    Assert.assertTrue(set.contains("ab"));
    Assert.assertTrue(set.contains("ac"));
    Assert.assertTrue(set.contains("bc"));

    set = StringSubSeq.getAllSubSeq("abcde");
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

  @Test
  public void testLongest() {
    String s1 = "abcde";
    String s2 = "1a2b3d4";
    String longest = StringSubSeq.getLongestSubSeq(s1, s2);
    Assert.assertEquals("abd", longest);

    s1 = "abcde";
    s2 = "abcde";
    longest = StringSubSeq.getLongestSubSeq(s1, s2);
    Assert.assertEquals("abcde", longest);

    s1 = "abcde";
    s2 = "123e45";
    longest = StringSubSeq.getLongestSubSeq(s1, s2);
    Assert.assertEquals("e", longest);

    s1 = "abcde";
    s2 = "1b2345d";
    longest = StringSubSeq.getLongestSubSeq(s1, s2);
    Assert.assertEquals("bd", longest);
  }

  @Test
  public void testLongestNone() {
    String s1 = "abcde";
    String s2 = "123";
    String longest = StringSubSeq.getLongestSubSeq(s1, s2);
    Assert.assertNull(longest);

    s1 = null;
    longest = StringSubSeq.getLongestSubSeq(s1, s2);
    Assert.assertNull(longest);

    s1 = "abcde";
    s2 = null;
    longest = StringSubSeq.getLongestSubSeq(s1, s2);
    Assert.assertNull(longest);

    s2 = "";
    longest = StringSubSeq.getLongestSubSeq(s1, s2);
    Assert.assertNull(longest);
  }
}
