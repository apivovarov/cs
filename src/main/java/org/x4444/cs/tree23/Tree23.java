package org.x4444.cs.tree23;

import java.util.LinkedList;
import java.util.List;

public class Tree23 {
    Node23 root = new Node23("0");

    public int[] add(int v) {
        FindRes r = root.find(v, 1, 0);
        return r.node.addV(v, 1, r.lCnt);
    }

    public Node23 find(int v) {
        FindRes n = root.find(v);
        return n.node;
    }

    public boolean contains(int v) {
        FindRes n = root.find(v);
        return n.node.contains(v);
    }

    public int[] get(int v) {
        FindRes r = root.find(v);
        return r.node.get(v, r.lCnt);
    }

    public int size() {
        return root.nCnt;
    }

    public void print() {
        System.out.println("--------------------------------------------------------------------");
        List<Node23> plan = new LinkedList<>();
        plan.add(root);
        while (!plan.isEmpty()) {
            List<Node23> plan2 = new LinkedList<>();
            for (Node23 n : plan) {
                System.out.println(n);
                for (Node23 ch : n.children) {
                    if (ch != null) {
                        plan2.add(ch);
                    }
                }
            }
            plan = plan2;
        }
    }
}
