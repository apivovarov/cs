package org.x4444.cs.tree;

import org.junit.Test;

import java.util.List;

public class TestTreeIter {

    @Test
    public void testReverse() {
        TreeIter d = new TreeIter();
        TreeIter.TreeEl root = d.genTree();
        d.reverse(root);
        List li = d.toList(root);
        assert(li.toString().equals("[17, 16, 15, 11, 10, 7, 6, 5, 1]"));
    }
}
