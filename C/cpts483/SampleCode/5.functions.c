#include <stdio.h>

int add_2(int a, int b) {
  int temp = a + b;
  return temp;
}

int add_3(int a, int b, int c) {
  int temp = a + b + c;
  return temp;
}

int main(int argc, char *argv[]) {
  int s = 0;

  for (int i = 0; i < argc; ++i) {
    s += add_2(i, i);
    s += add_3(i, i, i);
  }

  return 0;
}
