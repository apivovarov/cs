package org.x4444.cs.pow;

import org.junit.Assert;
import org.junit.Test;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Pow2Test {

    @Test
    public void isPow2Test() {
        Set<Integer> pow2 = new HashSet<>(Arrays.asList(1, 2, 4, 8, 16, 32));
        for (int i = 0; i < 40; i++) {
            Assert.assertEquals(pow2.contains(i), Pow2.isPow2(i));
        }
    }
}
