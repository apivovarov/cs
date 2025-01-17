#include <iostream>

int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;  // remainder
    a = temp;   // set a to the previous b
  }
  return a;
}

int lcm(int a, int b) {
  int p = a * b;
  if (p < 0) p = -p;
  return p / gcd(a, b);
}

int main() {
  int g = gcd(4, 18);
  std::cerr << "gcd: " << g << std::endl;
  int l = lcm(4, 18);
  std::cerr << "lcm: " << l << std::endl;
}
