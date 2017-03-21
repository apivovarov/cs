package org.x4444.cs.lcs;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

/**
 * TestLCS
 */
public class TestLCS {

    @Test
    public void testGetLen() {
        assertEquals(0, new LCS("", "").getLen());
        assertEquals(0, new LCS("a", "").getLen());
        assertEquals(0, new LCS("", "b").getLen());

        assertEquals(1, new LCS("abc", "a").getLen());
        assertEquals(1, new LCS("abc", "b").getLen());
        assertEquals(1, new LCS("abc", "c").getLen());
        assertEquals(1, new LCS("a", "abc").getLen());
        assertEquals(1, new LCS("b", "abc").getLen());
        assertEquals(1, new LCS("c", "abc").getLen());

        assertEquals(7, new LCS("nematode knowledge", "empty bottle").getLen());
    }
}
