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

        LCS lcs = new LCS("nematode knowledge", "empty bottles");
        assertEquals(7, lcs.getLen());
        lcs.printL();
    }

    @Test
    public void testGetLen2() {
        assertEquals(0, new LCS("", "").getLen2());
        assertEquals(0, new LCS("a", "").getLen2());
        assertEquals(0, new LCS("", "b").getLen2());

        assertEquals(1, new LCS("abc", "a").getLen2());
        assertEquals(1, new LCS("abc", "b").getLen2());
        assertEquals(1, new LCS("abc", "c").getLen2());
        assertEquals(1, new LCS("a", "abc").getLen2());
        assertEquals(1, new LCS("b", "abc").getLen2());
        assertEquals(1, new LCS("c", "abc").getLen2());

        LCS lcs = new LCS("nematode knowledge", "empty bottles");
        assertEquals(7, lcs.getLen2());
        lcs.printL();
    }
}
