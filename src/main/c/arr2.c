#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]) {

  char b1[] = "Hello";
  char *b2 = "world";

  char *b3;
  b3 = b1;
  printf("%s %s \n", b1, b2);
  printf("%p %lu\n", b3, sizeof(b3));
  printf("%p %lu\n", b1, sizeof(b1));
  printf("%p %lu\n", &b1, sizeof(&b1));

  int i1[] = {1,2,3,4,5,6};
  printf("%lu %lu %lu\n", sizeof(int), sizeof(i1), sizeof(i1) / sizeof(int));
}
