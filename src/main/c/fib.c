#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: fib <output_collection_size>\n");
    exit(-1);
  }

  int mx = sizeof(unsigned long) == 8 ? 94 : 47;

  unsigned int n, i;
  unsigned long a, b, c;

  sscanf(argv[1], "%u", &n);

  if (n < 3 || n > mx) {
    printf("Output collection size range is [3..%d]\n", mx);
    exit(-1);
  }

  a = 0;
  b = 1;
  printf("%lu\n%lu\n", a, b);
  for (i = 2; i < n; i++) {
    c = a + b;
    a = b;
    b = c;
    printf("%lu\n", c);
  }
}
