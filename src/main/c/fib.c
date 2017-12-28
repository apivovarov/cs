#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: fib <outut_collection_size>\n");
    exit(-1);
  }

  unsigned int a, b, c, n, i;

  sscanf(argv[1], "%d", &n);

  if (n < 3 || n > 47) {
    printf("Oututcollection size range is [3..47]\n");
    exit(-1);
  }

  a = 0;
  b = 1;
  printf("%d %d ", a, b);

  for (i = 2; i < n; i++) {
    c = a + b;
    a = b;
    b = c;
    printf("%d ", c);
  }
  printf("\n");
}
