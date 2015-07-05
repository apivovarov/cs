package org.x4444.cs.tree;

public class TreeIter {

  static class TreeEl {
    TreeEl l;
    TreeEl r;
    int v;

    public TreeEl() {
    }

    public TreeEl(int v) {
      this.v = v;
    }
  }

  public void iterTree(TreeEl el) {
    if (el == null) {
      return;
    }
    iterTree(el.l);
    System.out.println(el.v);
    iterTree(el.r);
  }

  public boolean contains(TreeEl root, int k) {
    if (root == null) {
      return false;
    }
    // go to left
    if (k < root.v) {
      return contains(root.l, k);
    } else if (k == root.v) {
      return true;
    } else {
      return contains(root.r, k);
    }
  }

  public TreeEl genTree() {
    // root. level 0 - 10
    TreeEl el10 = new TreeEl(10);
    // left on root
    TreeEl el7 = new TreeEl(7);
    TreeEl el6 = new TreeEl(6);
    TreeEl el5 = new TreeEl(5);
    TreeEl el1 = new TreeEl(1);
    // right on root
    TreeEl el17 = new TreeEl(17);
    TreeEl el16 = new TreeEl(16);
    TreeEl el15 = new TreeEl(15);
    TreeEl el11 = new TreeEl(11);

    // level 1 - 5, 15
    el10.l = el5;
    el10.r = el15;

    // level 2 - 1,7,11,17
    el5.l = el1;
    el5.r = el7;

    el15.l = el11;
    el15.r = el17;

    // level 3 - 6, 16
    el7.l = el6;
    el17.r = el16;

    return el10;
  }

  public static void main(String[] args) {
    TreeIter d = new TreeIter();
    TreeEl root = d.genTree();
    d.iterTree(root);

    System.out.println(d.contains(root, 5));
    System.out.println(d.contains(root, 15));
    System.out.println(d.contains(root, 17));
    System.out.println(d.contains(root, 4));
    System.out.println(d.contains(root, 0));
    System.out.println(d.contains(root, 100));
  }
}
