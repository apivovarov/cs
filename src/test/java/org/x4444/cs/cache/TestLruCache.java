package org.x4444.cs.cache;

import org.junit.Assert;

import org.junit.Test;
import org.x4444.cs.cache.LruCache;

public class TestLruCache {

  @Test
  public void testCache() {
    LruCache c = new LruCache(16, 16, 4);
    Object v = c.put(100, "v100");
    Assert.assertNull(v);
    Assert.assertEquals(1, c.size());

    v = c.put(200, "v200");
    Assert.assertNull(v);
    Assert.assertEquals(2, c.size());

    v = c.get(100);
    Assert.assertEquals("v100", v);

    Assert.assertEquals(100, c.mostRecentKey());
    Assert.assertEquals(200, c.leastRecentKey());

    v = c.put(300, "v300");
    v = c.put(400, "v400");
    v = c.put(500, "v500");

    Assert.assertEquals(500, c.mostRecentKey());
    Assert.assertEquals(200, c.leastRecentKey());

    v = c.get(100);
    v = c.get(200);
    v = c.get(300);
    v = c.get(400);
    v = c.get(500);

    Assert.assertEquals(500, c.mostRecentKey());
    Assert.assertEquals(100, c.leastRecentKey());

    v = c.remove(500);
    Assert.assertEquals(400, c.mostRecentKey());
    Assert.assertEquals(100, c.leastRecentKey());

    for (int i = 0; i < 12; i++) {
      v = c.put(i, "v" + i);
    }
    Assert.assertEquals(11, c.mostRecentKey());
    Assert.assertEquals(100, c.leastRecentKey());
    Assert.assertEquals(16, c.size());

    v = c.put(12, "v11");
    Assert.assertEquals(12, c.mostRecentKey());
    Assert.assertEquals(0, c.leastRecentKey());
    Assert.assertEquals(13, c.size());
  }
}
