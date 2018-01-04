#include "fib.h"

const int FIB_MX = sizeof(unsigned long) == 8 ? 94 : 47;

int *fib(int n, int arr[]) {
  if (n < 3 || n > FIB_MX) {
    printf("Output collection size range is [3..%d]\n", FIB_MX);
    return NULL;
  }
  unsigned int a = 0;
  unsigned int b = 1;
  arr[0] = a;
  arr[1] = b;
  for (int i = 2; i < n; i++) {
    unsigned int c = a + b;
#ifdef DEBUG
    printf("c addr %p \n", &c);
#endif
    a = b;
    b = c;
    arr[i] = c;
  }
  return arr;
}
