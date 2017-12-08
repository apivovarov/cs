package org.x4444.cs.tree23;

import java.util.Arrays;

public class Node23 {
    public String id;
    public El23[] elems = new El23[3];
    public Node23[] children = new Node23[4];
    public Node23 parent;
    public boolean isLeaf = true;

    public Node23(String id) {
        this.id = id;
    }

    public Node23 addV(int v) {
        return addV(v, 1);
    }

    Node23 addV(int v, int cnt) {
        if (elems[0] == null) {
            elems[0] = new El23(v, cnt);
            return getRoot();
        }

        boolean found = false;
        for (int i = 0; i < 3; i++) {
            if (elems[i] != null && elems[i].v == v) {
                elems[i].cnt += cnt;
                found = true;
                break;
            }
        }

        if (!found) {
            for (int i = 1; i >= 0; i--) {
                if (elems[i] == null) {
                    continue;
                }
                if (elems[i].v > v) {
                    elems[i + 1] = elems[i];
                    if (i == 0) {
                        elems[i] = new El23(v, cnt);
                    }
                } else {
                    elems[i + 1] = new El23(v, cnt);
                    break;
                }
            }
        }

        if (elems[2] != null) {
            return split();
        }
        return getRoot();
    }

    public Node23 find(int v) {
        if (isLeaf) {
            return this;
        }
        for (int i = 1; i >= 0; i--) {
            if (elems[i] == null) {
                continue;
            }
            if (elems[i].v == v) {
                return this;
            } else if (v > elems[i].v) {
                return children[i + 1].find(v);
            }
        }
        return children[0].find(v);
    }

    Node23 split() {
        Node23 lN = new Node23(id + "0");
        Node23 rN = new Node23(id + "1");
        id += "2";

        lN.elems[0] = elems[0];
        rN.elems[0] = elems[2];

        elems[0] = elems[1];
        elems[1] = null;
        elems[2] = null;

        if (!isLeaf) {
            lN.isLeaf = false;
            rN.isLeaf = false;

            lN.children[0] = children[0];
            lN.children[1] = children[1];
            rN.children[0] = children[2];
            rN.children[1] = children[3];
            lN.children[0].parent = lN;
            lN.children[1].parent = lN;
            rN.children[0].parent = rN;
            rN.children[1].parent = rN;
        }

        isLeaf = false;
        children[0] = lN;
        children[1] = rN;
        children[2] = null;
        children[3] = null;

        if (parent == null) {
            lN.parent = this;
            rN.parent = this;
            return this;
        } else {
            lN.parent = parent;
            rN.parent = parent;
            return parent.merge(this);
        }
    }

    Node23 merge(Node23 n) {
        replaceChild(n, n.children[0], n.children[1]);
        return addV(n.elems[0].v, n.elems[0].cnt);
    }

    void replaceChild(Node23 n, Node23 l, Node23 r) {
        for (int id = 2; id >= 0; id--) {
            if (children[id] == null) {
                continue;
            }
            if (children[id] == n) {
                children[id] = l;
                children[id + 1] = r;
                break;
            } else {
                children[id + 1] = children[id];
            }
        }
    }

    public Node23 getRoot() {
        if (parent == null) {
            return this;
        }
        return parent.getRoot();
    }

    public boolean contains(int v) {
        return getCnt(v) != null;
    }

    public Integer getCnt(int v) {
        for (El23 el : elems) {
            if (el != null && el.v == v) {
                return el.cnt;
            }
        }
        return null;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("[");
        for (int i = 0; i < 4; i++) {
            Node23 ch = children[i];
            if (ch != null) {
                if (sb.length() > 1) {
                    sb.append(",");
                }
                sb.append(ch.id);
            }
        }
        sb.append("]");
        return "id:" + id + ";elems:" + Arrays.toString(elems) + ";isLeaf:" + isLeaf + ";children:" + sb.toString()+ ";parent:" + (parent == null ? null : parent.id);
    }

    static class El23 {
        public int v;
        public int cnt;

        public El23(int v, int cnt) {
            this.v = v;
            this.cnt = cnt;
        }

        @Override
        public String toString() {
            return "{v:" + v + ";cnt:" + cnt + "}";
        }
    }
}
