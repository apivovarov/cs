package org.x4444.cs.expressions;

import org.junit.Assert;
import org.junit.Test;

/**
 * TestEval
 */
public class TestEval {

    @Test
    public void testEval() {
        Eval ev = new Eval();
        Assert.assertEquals(33, ev.eval("( + 1 ( * 3 ( + 1 1 ) 5 ) 2 )"));
    }
}
