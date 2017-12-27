package org.x4444.cs.heap;

import java.util.Arrays;

/**
 * Heap and heap sort impl inspired by https://www.youtube.com/watch?v=onlhnHpGgC4
 */
public class Heap {

    int capacity;

    int size = 0;

    int[] arr;

    public Heap(int capacity) {
        if (capacity < 1) {
            throw new IllegalArgumentException("Capacity should be more than 0");
        }
        this.capacity = capacity;
        arr = new int[capacity + 1];
    }

    public void add(int v) {
        if (size == capacity) {
            capacity *= 2;
            arr = Arrays.copyOf(arr, capacity + 1);
        }
        size++;
        arr[size] = v;
        //bubbleUp(size);
    }

    public void build() {
        if (size < 2) {
            return;
        }
        int half = size / 2;
        for (int i = half; i > 0; i--) {
            int cId = bubbleDown(i);
            bubbleUp(cId, i);
        }
    }

    void bubbleUp(int cId) {
        bubbleUp(cId, 1);
    }
    void bubbleUp(int cId, int maxPId) {
        if (cId <= maxPId) {
            return;
        }
        int pId = cId / 2;
        int p = arr[pId];
        int c = arr[cId];
        if (c <= p) {
            return;
        }
        arr[pId] = c;
        arr[cId] = p;
        bubbleUp(pId, maxPId);
    }

    int bubbleDown(int pId) {
        int cId1 = pId * 2;
        int cId2 = cId1 + 1;
        if (cId1 > size) {
            return pId;
        }
        int cId;
        if (cId2 > size) {
            cId = cId1;
        } else {
            int c1 = arr[cId1];
            int c2 = arr[cId2];
            cId = c1 >= c2 ? cId1 : cId2;
        }
        int p = arr[pId];
        int c = arr[cId];
        arr[pId] = c;
        arr[cId] = p;
        return bubbleDown(cId);
    }

    public int removeMax() {
        if (size == 0) {
            throw new IllegalArgumentException("Heap is empty");
        }
        int max = arr[1];
        arr[1] = arr[size];
        arr[size] = max;
        size--;
        if (size > 1) {
            int cId = bubbleDown(1);
            bubbleUp(cId);
        }
        return max;
    }

    public void sort() {
        int s = size;
        for (int i = 0; i < s; i++) {
            removeMax();
        }
    }

    public int max() {
        if (size == 0) {
            throw new IllegalArgumentException("Heap is empty");
        }
        return arr[1];
    }

    public int[] getArr() {
        return arr;
    }

    public int size() {
        return size;
    }

    public int capacity() {
        return capacity;
    }

    void print() {
        System.out.println(Arrays.toString(arr));
    }
}
