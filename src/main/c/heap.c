#include <stdlib.h>
#include <stdio.h>
#include <time.h>

unsigned int capacity = 20;

unsigned int size = 0;

int *arr;

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

void build() {
    if (size < 2) {
        return;
    }
    int half = size / 2;
    for (int i = half; i > 0; i--) {
        int cId = bubbleDown(i);
        bubbleUp(cId, i);
    }
}

void add(int v) {
//    if (size == capacity) {
//        capacity *= 2;
//        arr = Arrays.copyOf(arr, capacity + 1);
//    }
    size++;
    arr[size] = v;
}

int removeMax() {
    if (size == 0) {
        perror("Error: Heap is empty");
        return -1;
    }
    int max = arr[1];
    arr[1] = arr[size];
    arr[size] = max;
    size--;
    if (size > 1) {
        int cId = bubbleDown(1);
        bubbleUp(cId, 1);
    }
    return max;
}

void sort() {
    int s = size;
    for (int i = 0; i < s; i++) {
        removeMax();
    }
}

int max() {
    if (size == 0) {
        perror("Error: Heap is empty");
        return -1;
    }
    return arr[1];
}

void print(int max) {
    //printf("[");
    for (int i = 1; i <= max; i++) {
      printf("%d\n", arr[i]);
    }
    //printf("]\n");
}

void assertTrue(int r) {
  if (r == 0) {
    perror("Assert error: not true");
    exit(-1);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: heap <capacity>\n");
    exit(-1);
  }

  sscanf(argv[1], "%u", &capacity);

  arr = malloc((capacity + 1) * sizeof(int)) ;

  srand(time(0));
  for (int i = 1; i <= capacity; i++) {
    add(rand());
  }

  build();

  printf("Build:\n");
  print(size);

  for (int i = 1; i <= size / 2; i++) {
      assertTrue(arr[i] >= arr[i * 2]);
      if (i * 2 + 1 <= size) {
        assertTrue(arr[i] >= arr[i * 2 + 1]);
      }
  }

  int sz = size;
  sort();

  printf("\nSort:\n");
  print(sz);

  for (int i = 2; i <= sz; i++) {
    assertTrue(arr[i] >= arr[i - 1]);
  }
}