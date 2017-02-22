package org.x4444.cs.zones;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Zones
 * <p>
 * find zero zones surrounded by ones
 * <p>
 * 1 1 1 1 1 1 1 1
 * 1 1 1 1 0 1 1 1
 * 1 1 1 1 0 1 1 1
 * 1 1 1 1 1 1 1 1
 * 1 1 0 1 1 1 1 1
 * 1 1 0 1 1 1 1 1
 */
public class Zones {

    int[][] arr;

    int h;

    int w;

    public Zones(int[][] arr) {
        this.arr = arr;
        h = arr.length;
        assert h > 0;
        w = arr[0].length;
        assert w > 0;
    }

    public List<Set<Point>> find() {
        Set<Point> doneZeros = new HashSet<>();
        List<Set<Point>> res = new ArrayList<Set<Point>>();
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {

                int v = arr[r][c];

                if (v != 0) {
                    continue;
                }
                Point p = new Point(r, c);
                if (doneZeros.contains(p)) {
                    continue;
                }
                Set<Point> zone = findZone(p);
                doneZeros.addAll(zone);

                if (!isTouchingEdge(zone)) {
                    res.add(zone);
                }
            }
        }
        return res;
    }

    boolean isTouchingEdge(Collection<Point> points) {
        for (Point p : points) {
            if (p.r == 0 || p.c == 0 || p.c == w - 1 || p.r == h - 1) {
                return true;
            }
        }
        return false;
    }

    Set<Point> findZone(Point p) {
        Set<Point> zoneRes = new HashSet<Point>();
        zoneRes.add(p);
        Set<Point> plan = new HashSet<Point>();
        plan.add(p);

        return f2(plan, zoneRes);
    }

    Set<Point> f2(Set<Point> plan, Set<Point> zoneRes) {
        Set<Point> plan2 = new HashSet<Point>();
        for (Point p : plan) {
            Set<Point> neib = getNeib(p);
            for (Point p2 : neib) {
                int v = arr[p2.r][p2.c];
                if (v == 0) {
                    if (!zoneRes.contains(p2)) {
                        plan2.add(p2);
                        zoneRes.add(p2);
                    }
                }
            }
        }
        if (plan2.isEmpty()) {
            return zoneRes;
        }
        return f2(plan2, zoneRes);
    }

    Set<Point> getNeib(Point p) {
        Set<Point> res = new HashSet<Point>();
        if (p.r > 0) {
            res.add(new Point(p.r - 1, p.c));
        }
        if (p.r < h - 1) {
            res.add(new Point(p.r + 1, p.c));
        }
        if (p.c > 0) {
            res.add(new Point(p.r, p.c - 1));
        }
        if (p.c < w - 1) {
            res.add(new Point(p.r, p.c + 1));
        }
        return res;
    }

    static class Point {
        int r, c;

        public Point(int r, int c) {
            this.r = r;
            this.c = c;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o)
                return true;
            if (o == null || getClass() != o.getClass())
                return false;

            Point point = (Point) o;

            if (r != point.r)
                return false;
            return c == point.c;
        }

        @Override
        public int hashCode() {
            int result = r;
            result = 31 * result + c;
            return result;
        }

        @Override
        public String toString() {
            return "(" + r + "," + c + ")";
        }
    }
}
