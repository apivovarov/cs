package org.x4444.cs.str;

import java.io.Serializable;

/**
 * IntPair
 */
public class IntPair implements Serializable {

    public int a;
    public int b;

    public IntPair(int a, int b) {
        this.a = a;
        this.b = b;
    }

    @Override public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;

        IntPair intPair = (IntPair) o;

        if (a != intPair.a)
            return false;
        return b == intPair.b;
    }

    @Override public int hashCode() {
        int result = a;
        result = 31 * result + b;
        return result;
    }
}
