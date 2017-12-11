package org.x4444.cs.tree23;

import java.util.Arrays;

public class Node23 {
    public String id;
    public El23[] elems = new El23[3];
    public Node23[] children = new Node23[4];
    public Node23 parent;
    public boolean isLeaf = true;
    public int nCnt;

    public Node23(String id) {
        this.id = id;
    }

    int[] addV(int v, int cnt, int lCnt) {
        if (elems[0] == null) {
            elems[0] = new El23(v, cnt);
            return new int[] { lCnt, cnt };
        }

        boolean found = false;
        int vCnt = 0;
        for (int i = 0; i < 3; i++) {
            if (elems[i] != null && elems[i].v == v) {
                elems[i].cnt += cnt;
                vCnt = elems[i].cnt;
                lCnt = addLCnt(lCnt, i, true);
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
                    // shift
                    elems[i + 1] = elems[i];
                    if (i == 0) {
                        elems[i] = new El23(v, cnt);
                    }
                } else {
                    // put new element
                    elems[i + 1] = new El23(v, cnt);
                    lCnt = addLCnt(lCnt, i, false);
                    break;
                }
            }
            vCnt = cnt;
        }

        if (elems[2] != null) {
            split();
        }
        return new int[] { lCnt, vCnt };
    }

    int addLCnt(int lCnt, int id, boolean eq) {
        for (int i = 0; i <= id; i++) {
            if (children[i] != null) {
                lCnt += children[i].nCnt;
            }
            if (!(eq && i == id)) {
                lCnt += elems[i].cnt;
            }
        }
        return lCnt;
    }

    public FindRes find(int v) {
        return find(v, 0, 0);
    }

    public FindRes find(int v, int cnt, int lCnt) {
        nCnt += cnt;
        if (isLeaf) {
            return new FindRes(this, lCnt);
        }
        for (int i = 1; i >= 0; i--) {
            if (elems[i] == null) {
                continue;
            }
            if (elems[i].v == v) {
                return new FindRes(this, lCnt);
            } else if (v > elems[i].v) {
                lCnt = addLCnt(lCnt, i, false);
                return children[i + 1].find(v, cnt, lCnt);
            }
        }
        return children[0].find(v, cnt, lCnt);
    }

    void split() {
        Node23 lN = new Node23(id + "0");
        Node23 rN = new Node23(id + "1");
        id += "2";

        lN.elems[0] = elems[0];
        rN.elems[0] = elems[2];
        lN.nCnt += lN.elems[0].cnt;
        rN.nCnt += rN.elems[0].cnt;

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

            lN.nCnt += lN.children[0].nCnt;
            lN.nCnt += lN.children[1].nCnt;
            rN.nCnt += rN.children[0].nCnt;
            rN.nCnt += rN.children[1].nCnt;
        }

        isLeaf = false;
        children[0] = lN;
        children[1] = rN;
        children[2] = null;
        children[3] = null;

        if (parent == null) {
            lN.parent = this;
            rN.parent = this;
        } else {
            lN.parent = parent;
            rN.parent = parent;
            parent.merge(this);
        }
    }

    void merge(Node23 n) {
        replaceChild(n, n.children[0], n.children[1]);
        addV(n.elems[0].v, n.elems[0].cnt, 0);
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

    public boolean contains(int v) {
        return get(v, 0) != null;
    }

    public int[] get(int v, int lCnt) {
        for (int i = 0; i < elems.length; i++) {
            El23 el = elems[i];
            if (el != null && el.v == v) {
                lCnt = addLCnt(lCnt, i, true);
                return new int[] { lCnt, el.cnt };
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
        return "id:" + id + ";elems:" + Arrays.toString(elems) + ";isLeaf:" + isLeaf + ";children:" + sb.toString() + ";parent:" + (
            parent == null ? null : parent.id) + ";nCnt:" + nCnt;
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
