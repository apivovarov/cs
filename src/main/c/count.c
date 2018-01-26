#include <stdio.h>

void putcharVerb(int c);

int main() {
    int c;
    long nCnt = 0;
    long blank = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            ++nCnt;
            ++blank;
        } else {
           blank = 0;
        }
        if (blank <= 1) {
            putcharVerb(c);
        }
    }
    printf("Blank count: %ld\n", nCnt);
}

void putcharVerb(int c) {
  if (c == '\t') {
      putchar('\\');
      putchar('t');
  } else if (c == '\\') {
      putchar('\\');
      putchar('\\');
  } else {
      putchar(c);
  }
}
