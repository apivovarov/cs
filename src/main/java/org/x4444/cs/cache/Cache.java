package org.x4444.cs.cache;


public interface Cache {

  Object get(Object key);

  Object put(Object key, Object value);

  Object remove(Object key);

  int size();
}
