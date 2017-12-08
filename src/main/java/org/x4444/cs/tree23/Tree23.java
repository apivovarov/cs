package org.x4444.cs.tree23;

import java.util.LinkedList;
import java.util.List;

public class Tree23 {
    Node23 root = new Node23("0");

    public Node23 add(int v) {
        Node23 n = root.find(v);
        return n.addV(v);
    }

    public Node23 find(int v) {
        Node23 n = root.find(v);
        return n;
    }

    public boolean contains(int v) {
        Node23 n = root.find(v);
        return n.contains(v);
    }

    public Integer getCnt(int v) {
        Node23 n = root.find(v);
        return n.getCnt(v);
    }

    public void print() {
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
