package org.x4444.cs.zones;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.junit.Assert;
import org.junit.Test;

/**
 * TestZones
 */
public class TestZones {

    @Test
    public void testFind() {
        int[][] arr = new int[6][8];
        arr[0] = new int[] {1, 1, 1, 1, 1, 1, 0, 1};
        arr[1] = new int[] {1, 1, 1, 1, 0, 1, 1, 1};
        arr[2] = new int[] {1, 0, 1, 0, 0, 0, 1, 1};
        arr[3] = new int[] {1, 1, 1, 1, 0, 1, 1, 1};
        arr[4] = new int[] {1, 1, 0, 0, 1, 1, 1, 1};
        arr[5] = new int[] {1, 1, 0, 1, 1, 1, 1, 1};
        Zones z = new Zones(arr);
        List<Set<Zones.Point>> res = z.find();
        Assert.assertEquals(2, res.size());

        Set<Zones.Point> res1 = new HashSet<Zones.Point>();
        res1.add(new Zones.Point(1, 4));
        res1.add(new Zones.Point(2, 3));
        res1.add(new Zones.Point(2, 4));
        res1.add(new Zones.Point(2, 5));
        res1.add(new Zones.Point(3, 4));

        Set<Zones.Point> res2 = new HashSet<Zones.Point>();
        res2.add(new Zones.Point(2, 1));

        Assert.assertTrue(res.contains(res1));
        Assert.assertTrue(res.contains(res2));
    }
}
