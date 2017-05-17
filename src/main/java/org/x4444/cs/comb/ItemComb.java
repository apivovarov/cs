package org.x4444.cs.comb;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

/**
 * ItemComb
 */
public class ItemComb {

    public static List<String> getComb(String input) {
        LinkedList<Character> out = new LinkedList();
        for (char c : input.toCharArray()) {
            out.add(c);
        }
        return getCombInternal(out);
    }

    public static List<String> getComb(List<Character> input) {
        return getComb(new LinkedList<>(input));
    }

    protected static List<String> getCombInternal(LinkedList<Character> input) {
        if (input == null || input.isEmpty()) {
            return null;
        }
        if (input.size() == 1) {
            return Arrays.asList(input.get(0).toString());
        }
        if (input.size() > 31) {
            throw new IllegalArgumentException("max input length is 31");
        }

        int total = (int) Math.pow(2, input.size()) - 1;

        List<String> out = new ArrayList<String>(total);
        getCombInternal(input, out);
        return out;
    }

    protected static void getCombInternal(LinkedList<Character> input, List<String> out) {
        if (input.size() == 1) {
            out.add(input.get(0).toString());
            return;
        }
        String head = input.removeFirst().toString();
        getCombInternal(input, out);
        List<String> buffOut = new ArrayList<String>(out.size());
        for (String outV : out) {
            buffOut.add(head + outV);
        }
        out.add(head);
        out.addAll(buffOut);
    }
}
