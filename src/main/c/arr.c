#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "fib.h"

int main(int argc, char* argv[]) {

  FILE *fp = fopen("/tmp/test", "w");

  char buf[200];

  for (int i = 0; i < 10; i++) {
    fprintf(fp, "%d: This is test\n", i);
  }

  fclose(fp);

  fp = fopen("/tmp/test", "r");

  for (int i = 0; i < 10; i++) {
    fgets(buf, 200, fp);
    //fscanf(fp2, "%s", buf);
    printf("%s", buf);

  }

  fclose(fp);

  unsigned int n;
  sscanf(argv[1], "%u", &n);

  int arr[n];
  int *res = fib(n, arr);
  if (!res) {
    exit(3);
  }
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  printf("FF: %d \n", FIB_MX);
}