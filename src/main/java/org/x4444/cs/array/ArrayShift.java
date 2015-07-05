package org.x4444.cs.array;

public class ArrayShift {

  public static void shiftLeft(int[] in, int shift) {
    if (in == null || shift <= 0 || in.length == 0 || shift == in.length) {
      return;
    }
    if (shift > in.length) {
      // adjust shift value
      shift %= in.length;
    }
    int pos = shift;
    while (pos < in.length) {
      int tmp = in[pos];

      shiftByOne(in, pos, shift);
      in[pos - shift] = tmp;
      pos++;
    }
  }

  static void shiftByOne(int[] in, int pos, int shift) {
    int lastEl = pos - shift;
    while (pos > lastEl) {
      in[pos] = in[pos - 1];
      pos--;
    }
  }
}
