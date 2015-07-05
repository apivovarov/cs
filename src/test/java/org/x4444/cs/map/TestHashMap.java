package org.x4444.cs.map;

import org.junit.Assert;
import org.junit.Test;
import org.x4444.cs.map.HashMap;
import org.x4444.cs.map.Map;

public class TestHashMap {

  @Test
  public void testPutGetRemove1() {
    Map m = new HashMap();
    Assert.assertEquals(0, m.size());
    Assert.assertEquals(16, m.capacity());

    m.put(1, "v1");
    Assert.assertEquals(1, m.size());
    Assert.assertEquals(16, m.capacity());

    Object v = m.get(1);
    Assert.assertEquals("v1", v);
    Assert.assertEquals(1, m.size());
    Assert.assertEquals(16, m.capacity());

    v = m.get(10);
    Assert.assertNull(v);

    Object prevV = m.put(1, "s1");
    Assert.assertEquals("v1", prevV);
    Assert.assertEquals(1, m.size());
    Assert.assertEquals(16, m.capacity());

    v = m.get(1);
    Assert.assertEquals("s1", v);
    Assert.assertEquals(1, m.size());
    Assert.assertEquals(16, m.capacity());

    v = m.remove(1);
    Assert.assertEquals("s1", v);
    Assert.assertEquals(0, m.size());
    Assert.assertEquals(16, m.capacity());

    v = m.get(1);
    Assert.assertNull(v);
    Assert.assertEquals(0, m.size());
    Assert.assertEquals(16, m.capacity());

    prevV = m.put(1, "s1");
    Assert.assertNull(prevV);
    Assert.assertEquals(1, m.size());
    Assert.assertEquals(16, m.capacity());

    v = m.get(1);
    Assert.assertEquals("s1", v);
    Assert.assertEquals(1, m.size());
    Assert.assertEquals(16, m.capacity());

    v = m.put(2, "s2");
    Assert.assertNull(v);
    Assert.assertEquals(2, m.size());
    Assert.assertEquals(16, m.capacity());

    v = m.get(2);
    Assert.assertEquals("s2", v);
    Assert.assertEquals(2, m.size());
    Assert.assertEquals(16, m.capacity());
  }

  @Test
  public void testGrow() {
    Map m = new HashMap();

    for (int i = 16; i < 32; i++) {
      m.put(i, "v" + i);
    }
    Assert.assertEquals(16, m.size());
    Assert.assertEquals(16, m.capacity());

    Object v = m.get(16);
    Assert.assertEquals("v16", v);

    v = m.get(31);
    Assert.assertEquals("v31", v);

    m.put(32, "v32");
    Assert.assertEquals(17, m.size());
    Assert.assertEquals(32, m.capacity());

    v = m.get(16);
    Assert.assertEquals("v16", v);
    v = m.get(16);
    Assert.assertEquals("v16", v);

    v = m.get(17);
    Assert.assertEquals("v17", v);
    v = m.get(17);
    Assert.assertEquals("v17", v);

    v = m.get(31);
    Assert.assertEquals("v31", v);
    v = m.get(31);
    Assert.assertEquals("v31", v);

    v = m.get(32);
    Assert.assertEquals("v32", v);
    v = m.get(32);
    Assert.assertEquals("v32", v);

    // test grow two times
    m.put(62, "v62");
    Assert.assertEquals(18, m.size());
    Assert.assertEquals(32, m.capacity());

    for (int i = 133; i < 148; i++) {
      m.put(i, "v" + i);
    }
    Assert.assertEquals(33, m.size());
    Assert.assertEquals(48, m.capacity());

    for (int i = 148; i < 164; i++) {
      m.put(i, "v" + i);
    }
    Assert.assertEquals(49, m.size());
    Assert.assertEquals(64, m.capacity());

    v = m.get(62);
    Assert.assertEquals("v62", v);
  }

  @Test
  public void testCollision() {
    Obj o100 = new Obj(100, "v100");
    Obj o101 = new Obj(100, "v101");
    Obj o102 = new Obj(100, "v102");

    Map m = new HashMap();
    Object v = m.put(o100, "vv100");
    Assert.assertNull(v);
    v = m.put(o101, "vv101");
    Assert.assertNull(v);

    v = m.get(o100);
    Assert.assertEquals("vv100", v);
    v = m.get(o101);
    Assert.assertEquals("vv101", v);
    v = m.get(o102);
    Assert.assertNull(v);
    Assert.assertEquals(2, m.size());
    Assert.assertEquals(16, m.capacity());

    v = m.remove(o101);
    Assert.assertEquals("vv101", v);
    v = m.get(o101);
    Assert.assertNull(v);
    Assert.assertEquals(1, m.size());
    Assert.assertEquals(16, m.capacity());

    v = m.remove(o102);
    Assert.assertNull(v);
    Assert.assertEquals(1, m.size());
    Assert.assertEquals(16, m.capacity());
  }

  @Test
  public void testPutAndRehash() {
    Map m = new HashMap();
    Assert.assertEquals(0, m.size());
    Assert.assertEquals(16, m.capacity());

    m.put(62, "v62");
    Assert.assertEquals(1, m.size());
    Assert.assertEquals(16, m.capacity());

    for (int i = 100; i < 150; i++) {
      m.put(i, "v" + i);
    }

    Assert.assertEquals(51, m.size());
    Assert.assertEquals(64, m.capacity());

    Object v = m.put(62, "s62");
    Assert.assertEquals("v62", v);
    Assert.assertEquals(51, m.size());
    Assert.assertEquals(64, m.capacity());

    v = m.get(62);
    Assert.assertEquals("s62", v);
    Assert.assertEquals(51, m.size());
    Assert.assertEquals(64, m.capacity());
  }

  @Test
  public void testRemoveAndRehash() {
    Map m = new HashMap();
    Assert.assertEquals(0, m.size());
    Assert.assertEquals(16, m.capacity());

    m.put(62, "v62");
    Assert.assertEquals(1, m.size());
    Assert.assertEquals(16, m.capacity());

    for (int i = 100; i < 150; i++) {
      m.put(i, "v" + i);
    }

    Assert.assertEquals(51, m.size());
    Assert.assertEquals(64, m.capacity());

    Object v = m.remove(62);
    Assert.assertEquals("v62", v);
    Assert.assertEquals(50, m.size());
    Assert.assertEquals(64, m.capacity());

    v = m.get(62);
    Assert.assertNull(v);
    Assert.assertEquals(50, m.size());
    Assert.assertEquals(64, m.capacity());
  }

  static class Obj {
    int k;
    String v;

    public Obj() {
    }

    public Obj(int k, String v) {
      super();
      this.k = k;
      this.v = v;
    }

    @Override
    public int hashCode() {
      final int prime = 31;
      int result = 1;
      result = prime * result + k;
      return result;
    }

    @Override
    public boolean equals(Object obj) {
      if (this == obj)
        return true;
      if (obj == null)
        return false;
      if (getClass() != obj.getClass())
        return false;
      Obj other = (Obj) obj;
      if (k != other.k)
        return false;
      if (v == null) {
        if (other.v != null)
          return false;
      } else if (!v.equals(other.v))
        return false;
      return true;
    }
  }
}
