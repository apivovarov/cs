#include "fib.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: fib <output_collection_size>\n");
    exit(1);
  }

  unsigned int n, i;
  unsigned long a, b, c;

  sscanf(argv[1], "%u", &n);

  int arr[n];
  int *res = fib(n, arr);
  if (!res) {
    exit(3);
  }
  for (i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
