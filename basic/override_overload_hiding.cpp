#include <cstdio>

class A {
 public:
  void fun1(int a) {
    printf("A: fun1(int)\n");
  }
  virtual void fun2(int a) {
    printf("A: fun2(int)\n");
  }

  void fun3(int a) {
    printf("A: fun3(int)\n");
  }
};

class B : A {
 public:
  void fun1(float a) {
    printf("B: fun1(float)\n");
  }
  virtual void fun2(float a) {
    printf("B: fun2(float)\n");
  }

  void fun3(int a) {
    printf("B: fun3(int)\n");
  }
};
int main() {
  B b;

  b.fun1(1.0f);
  b.fun2(1.0f);
  b.fun3(1);
  return 0;
}
