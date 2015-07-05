package org.x4444.cs.map;

public interface Map {

  /**
   * Puts key and value to HashMap
   * @param key
   * @param value
   * @return previous value or null if no previous value
   */
  Object put(Object key, Object value);

  /**
   * Gets Value by Key
   * @param key
   * @return value or null if entity was not found
   */
  Object get(Object key);

  /**
   * Removes Entity form the map
   * @param key
   * @return previous value or null if entity was not found
   */
  Object remove(Object key);

  /**
   * Returns number of elements in the HashMaps
   * @return size
   */
  int size();

  /**
   * Returns the capacity of the HashMap
   * @return capacity
   */
  int capacity();
}
