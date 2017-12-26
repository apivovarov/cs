package org.x4444.cs.impl;

import org.junit.Assert;
import org.junit.Test;

import java.io.FileNotFoundException;
import java.io.InputStream;

public class EmasSupercomputerTest {

    @Test
    public void test1() throws FileNotFoundException {
        InputStream is = getClass().getResourceAsStream("/ema1.txt");
        EmasSupercomputer.init(is);
        int sq = EmasSupercomputer.findMaxSq();
        Assert.assertEquals(5, sq);
    }

    @Test
    public void test2() throws FileNotFoundException {
        InputStream is = getClass().getResourceAsStream("/ema2.txt");
        EmasSupercomputer.init(is);
        int sq = EmasSupercomputer.findMaxSq();
        Assert.assertEquals(25, sq);
    }
}
