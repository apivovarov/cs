package org.x4444.cs.list;

import org.junit.Assert;
import org.junit.Test;

import java.util.Arrays;
import java.util.List;

/**
 * TestListUtils
 */
public class TestListUtils {

    @Test
    public void testFlatten() {
        List<?> list = Arrays.asList(1, 5, Arrays.asList(4, 2, Arrays.asList(8, 5, 7)), 9);
        List<Integer> res = ListUtils.flatten(list, Integer.class);
        Assert.assertEquals(Arrays.asList(1, 5, 4, 2, 8, 5, 7, 9), res);
    }

    @Test
    public void testFlattenFail() {
        List<?> list = Arrays.asList(1, 5, Arrays.asList("4", "2.55", Arrays.asList(8, 5, 7)), 9);
        try {
            List<Integer> res = ListUtils.flatten(list, Integer.class);
            Assert.fail("flatten should throw RuntimeException");
        } catch (RuntimeException e) {
            System.out.println(e.getMessage());
        }
    }
}
