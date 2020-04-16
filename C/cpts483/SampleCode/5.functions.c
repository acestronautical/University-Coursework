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

    s = s + add_2(2, 3);
    s = s + add_3(4, 5, 6);
  

  return 0;
}

// clang -O0 -Xclang -disable-O0-optnone -S -emit-llvm 5.functions.c  -o test.ll
// opt -load ~/repos/llvm-project/build/lib/LLVMHW3.so -HW -S test.ll  -o dev.ll
// clang dev.ll