#include <stdio.h>

int main() {
  const volatile int a = 10;
  const int b = 10;
  int* pa = (int*)&a;
  *pa = 20;

  int* pb = (int*)&b;
  *pb = 20;

  printf("a:%d  *pa=%d\n", a, *pa); // 20 20
  printf("a:%d  *pb=%d\n", b, *pb); // 10 20
}
