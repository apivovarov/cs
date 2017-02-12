package org.x4444.cs.expressions;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Eval. Evaluates expressions like ( + 3 5 7 )
 */
public class Eval {

    /**
     * Evaluates expressions like ( + 3 5 7 )
     * Supports + and * operations, e.g. ( + 1 ( * 3 ( + 1 1 ) 5 ) 2 ) = 33
     *
     * @param s
     * @return
     */
    public int eval(String s) {
        String[] arr = s.split(" ");
        return ovToInt(arrToOpVal(arr));
    }

    protected int ovToInt(OpVal ov) {
        int res = 0;
        if ("*".equals(ov.op)) {
            res = 1;
        }
        for (Object s : ov.values) {
            int v;
            if (s instanceof String) {
                v = Integer.parseInt((String) s);
            } else {
                v = ovToInt(arrToOpVal((String[]) s));
            }
            if ("*".equals(ov.op)) {
                res *= v;
            } else if ("+".equals(ov.op)) {
                res += v;
            }
        }
        return res;
    }

    protected OpVal arrToOpVal(String[] arr) {
        assert arr.length >= 4;
        assert "(".equals(arr[0]) && ")".equals(arr[arr.length - 1]);
        OpVal ov = new OpVal();
        ov.values = new ArrayList<Object>();
        int st = 0;
        int bCnt = 0;
        ov.op = arr[1];
        assert "*".equals(ov.op) || "+".equals(ov.op);
        for (int i = 2; i < arr.length - 1; i++) {
            if (arr[i].equals("(")) {
                if (bCnt == 0) {
                    st = i;
                }
                bCnt++;
            } else if (arr[i].equals(")")) {
                bCnt--;
                if (bCnt == 0) {
                    ov.values.add(Arrays.copyOfRange(arr, st, i + 1));
                }
            } else {
                if (bCnt == 0) {
                    ov.values.add(arr[i]);
                }
            }

        }
        assert bCnt == 0;
        return ov;
    }

    public static class OpVal {
        String op;
        List<Object> values;
    }
}
