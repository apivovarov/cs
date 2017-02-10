package org.x4444.cs.str;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Permutations
 */
public class Permutations {
    public List<IntPair> find(String a, String b) {
        List<IntPair> res = new ArrayList<IntPair>();
        if (a == null || a.isEmpty() || b == null || b.isEmpty()) {
            return res;
        }

        Map<Character, Integer> bMap = countChars(b);

        Map<Character, Integer> map = new HashMap<Character, Integer>();

        for (int i = 0; i < a.length(); i++) {
            char addCh = a.charAt(i);
            addToMap(map, addCh);
            int j = i - b.length();
            if (j >= 0) {
                char rmCh = a.charAt(j);
                rmFromMap(map, rmCh);
            }
            if (j >= -1) {
                if (isEq(map, bMap)) {
                    res.add(new IntPair(j + 1, i));
                }
            }
        }

        return res;
    }

    void addToMap(Map<Character, Integer> map, char ch) {
        Integer cnt = map.getOrDefault(ch, 0);
        map.put(ch, ++cnt);
    }

    void rmFromMap(Map<Character, Integer> map, char ch) {
        Integer cnt = map.remove(ch);
        if (cnt != null && cnt > 1) {
            map.put(ch, cnt - 1);
        }
    }

    Map<Character, Integer> countChars(String s) {
        Map<Character, Integer> chMap = new HashMap<Character, Integer>();
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            addToMap(chMap, ch);
        }
        return chMap;
    }

    boolean isEq(Map<Character, Integer> m1, Map<Character, Integer> m2) {
        if (m1.size() != m2.size()) {
            return false;
        }
        for (Map.Entry<Character, Integer> e : m1.entrySet()) {
            Integer v2 = m2.get(e.getKey());
            if (v2 == null || v2 != e.getValue()) {
                return false;
            }
        }
        return true;
    }
}
