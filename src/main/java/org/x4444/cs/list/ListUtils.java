package org.x4444.cs.list;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * ListUtils
 */
public class ListUtils {

    public static <T> List<T> flatten(List<?> in, Class cc) {
        if (in == null) {
            return null;
        }
        if (in.isEmpty()) {
            return new ArrayList<T>(0);
        }
        LinkedList<T> acc = new LinkedList<T>();

        walk(acc, in, cc);

        return acc;
    }

    protected static <T> void walk(LinkedList<T> acc, List<?> in, Class cc) {
        for (Object v : in) {
            if (v instanceof List) {
                walk(acc, (List) v, cc);
            } else {
                if (!cc.isInstance(v)) {
                    throw new RuntimeException("Element is not the instance of " + cc);
                }
                acc.add((T) v);
            }
        }
    }
}
