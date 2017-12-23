package org.x4444.cs.lcs;

import java.util.Arrays;

import org.junit.Assert;
import org.junit.Test;

/**
 * TestLCS
 */
public class TestLCSInt {

    @Test
    public void testFillMatrix() {
        LCSInt l = new LCSInt(new int[] { 65, 66, 67, 68, 65 }, new int[] { 65, 67, 66, 68, 69, 65 });
        l.fillMatrix();
        l.printMatrix();
        int[] res = l.walkMatrix();
        String resS = Arrays.toString(res);
        System.out.println(resS);
        Assert.assertTrue("[65, 67, 68, 65]".equals(resS) || "[65, 66, 68, 65]".equals(resS));
    }

    @Test
    public void testFindLcs() {
        LCSInt l = new LCSInt(new int[] { 65, 66, 67, 68, 65 }, new int[] { 65, 67, 66, 68, 69, 65 });
        int[] res = l.findLcs();
        String resS = Arrays.toString(res);
        System.out.println(resS);
        Assert.assertTrue("[65, 67, 68, 65]".equals(resS) || "[65, 66, 68, 65]".equals(resS));
    }

    @Test
    public void testFindLcs2() {
        String s1 = "16 27 89 79 60 76 24 88 55 94 57 42 56 74 24 95 55 33 69 29 14 7 94 41 8 71 12 15 43 3 23 49 84 78 73 63 5 46 98 26 40 76 41 89 24 20 68 14 88 26";
        String s2 = "27 76 88 0 55 99 94 70 34 42 31 47 56 74 69 46 93 88 89 7 94 41 68 37 8 71 57 15 43 89 43 3 23 35 49 38 84 98 47 89 73 24 20 14 88 75";
        String s3 = "27 76 88 55 94 42 56 74 69 7 94 41 8 71 15 43 3 23 49 84 98 89 24 20 14 88";

        int[] a1 = getArr(s1);
        int[] a2 = getArr(s2);
        int[] exp = getArr(s3);
        LCSInt l = new LCSInt(a1, a2);
        int[] res = l.findLcs();
        String resS = Arrays.toString(res);
        System.out.println(resS);
        Assert.assertEquals(Arrays.toString(exp), resS);
    }

    static int[] getArr(String s) {
        String[] a = s.split(" ");
        int[] arr = new int[a.length];
        for (int i = 0; i < a.length; i++) {
            arr[i] = Integer.parseInt(a[i]);
        }
        return arr;
    }
}
