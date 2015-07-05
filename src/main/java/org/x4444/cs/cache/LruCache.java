package org.x4444.cs.cache;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;

public class LruCache implements Cache {

  protected final HashMap<Object, ValueAndTime> map;
  protected final TreeMap<Long, Object> usageTree = new TreeMap<Long, Object>();

  protected final int maxSize;
  protected final int cleanBatchSize;

  long lastTime;

  public static class ValueAndTime {
    Object value;
    Long time;

    public ValueAndTime() {
    }

    public ValueAndTime(Object value, Long time) {
      this.value = value;
      this.time = time;
    }
  }

  public LruCache(int initialCapacity, int maxSize, int cleanBatchSize) {
    this.maxSize = maxSize;
    this.cleanBatchSize = cleanBatchSize;

    map = new HashMap<Object, ValueAndTime>(initialCapacity);
  }

  @Override
  public Object get(Object key) {
    if (key == null) {
      throw new IllegalArgumentException("Key is null");
    }

    ValueAndTime vt = map.get(key);
    if (vt == null) {
      return null;
    }

    usageTree.remove(vt.time);
    vt.time = getTime();
    usageTree.put(vt.time, key);

    return vt.value;
  }

  @Override
  public Object put(Object key, Object value) {
    if (key == null) {
      throw new IllegalArgumentException("Key is null");
    }

    if (map.size() >= maxSize) {
      clean();
    }

    Object oldValue;
    ValueAndTime vt = map.get(key);
    long time = getTime();
    if (vt == null) {
      // add new entry to both map and usageTree
      vt = new ValueAndTime(value, time);
      map.put(key, vt);
      usageTree.put(time, key);
      oldValue = null;
    } else {
      // update value and time
      usageTree.remove(vt.time);
      usageTree.put(time, key);

      oldValue = vt.value;
      vt.value = value;
      vt.time = time;
    }

    return oldValue;
  }

  @Override
  public Object remove(Object key) {
    if (key == null) {
      throw new IllegalArgumentException("Key is null");
    }
    ValueAndTime vt = map.remove(key);
    if (vt == null) {
      return null;
    }
    usageTree.remove(vt.time);
    return vt.value;
  }

  protected void clean() {
    Iterator<Map.Entry<Long, Object>> iter = usageTree.entrySet().iterator();

    for (int i = 0; iter.hasNext() && i < cleanBatchSize; i++) {
      Map.Entry<Long, Object> e = iter.next();
      iter.remove();
      map.remove(e.getValue());
    }
  }

  @Override
  public int size() {
    assert map.size() == usageTree.size();
    return map.size();
  }

  public Object leastRecentKey() {
    Map.Entry<Long, Object> firstEntry = usageTree.firstEntry();
    if (firstEntry == null) {
      return null;
    }
    return firstEntry.getValue();
  }

  public Object mostRecentKey() {
    Map.Entry<Long, Object> lastEntry = usageTree.lastEntry();
    if (lastEntry == null) {
      return null;
    }
    return lastEntry.getValue();
  }

  protected long getTime() {
    long ms = System.currentTimeMillis() * 1000;
    if (ms <= lastTime) {
      ms = lastTime + 1;
    }
    lastTime = ms;
    return ms;
  }
}
