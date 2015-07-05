package org.x4444.cs.map;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class HashMap implements Map {

  public static class Entity {

    public Object key;
    public Object value;

    public Entity() {
    }

    public Entity(Object key, Object value) {
      this.key = key;
      this.value = value;
    }
  }

  private final int tableSize;
  private int size;
  private int cap;

  private List<LinkedList<Entity>[]> tables = new ArrayList<LinkedList<Entity>[]>();

  /**
   * Constructs HashMap with initial capacity 16.
   */
  public HashMap() {
    this(16);
  }

  /**
   * Constructs HashMap with specified capacity tableSize.<br>
   * tableSize is also used as increment by capacity.
   *
   * @param tableSize
   *          initial HashMap capacity.
   */
  public HashMap(int tableSize) {
    if (tableSize < 1) {
      throw new IllegalArgumentException("tableSize should be 1 or more");
    }
    this.tableSize = tableSize;
    grow();
  }

  @Override
  public Object put(Object key, Object value) {
    if (key == null) {
      throw new IllegalArgumentException("Key is null");
    }

    if (size >= cap) {
      grow();
    }

    Entity e = getEntityAndRehash(key);
    if (e != null) {
      Object exVal = e.value;
      e.value = value;
      return exVal;
    }

    // value not found
    // find place and add Entity
    e = findEntity(key, cap, false, true, new Entity(key, value));
    return null;
  }

  protected Entity findEntity(Object key, int thecap, boolean remove, boolean add, Entity entityToAdd) {
    if (key == null) {
      throw new IllegalArgumentException("Key is null");
    }

    // get Table and Row
    int globalIdx = Math.abs(key.hashCode()) % thecap;
    int idx = globalIdx % tableSize;
    LinkedList<Entity>[] table = getTable(globalIdx);
    LinkedList<Entity> row = table[idx];
    if (row == null) {
      if (!add) {
        return null;
      }
      table[idx] = row = new LinkedList<Entity>();
    } else {

      Iterator<Entity> iter = row.iterator();
      while (iter.hasNext()) {
        Entity e = iter.next();
        if (key.equals(e.key)) {
          if (remove) {
            iter.remove();
            size--;
          }
          return e;
        }
      }
    }

    if (add) {
      row.add(entityToAdd);
      size++;
      return entityToAdd;
    }

    return null;
  }

  protected Entity getEntityAndRehash(Object key) {
    Entity e = findEntity(key, cap, false, false, null);
    if (e != null) {
      return e;
    }
    for (int i = cap - tableSize; i > 0; i -= tableSize) {
      e = findEntity(key, i, true, false, null);
      // if found on old address then rehash
      if (e != null) {
        findEntity(key, cap, false, true, e);
        return e;
      }
    }

    return null;
  }

  @Override
  public Object get(Object key) {
    Entity e = getEntityAndRehash(key);
    return e != null ? e.value : null;
  }

  @Override
  public Object remove(Object key) {
    for (int i = cap; i > 0; i -= tableSize) {
      Entity e = findEntity(key, i, true, false, null);
      // if found on old address then rehash
      if (e != null) {
        return e.value;
      }
    }
    return null;
  }

  protected void grow() {
    @SuppressWarnings("unchecked")
    LinkedList<Entity>[] ll = new LinkedList[tableSize];
    tables.add(ll);
    cap += tableSize;
  }

  protected LinkedList<Entity>[] getTable(int globalIdx) {
    int tableId = globalIdx / tableSize;
    LinkedList<Entity>[] table = tables.get(tableId);
    return table;
  }

  @Override
  public int size() {
    return size;
  }

  @Override
  public int capacity() {
    return cap;
  }
}
