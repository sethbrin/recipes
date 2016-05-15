#include <iostream>

using namespace std;

#pragma pack(8)

struct One {
  double d;
  char c;
  int i;
}; // 8 + 1 + 3(padding) + 4 = 12 + 4 = 16

struct Two {
  char c;
  double d;
  int i;
}; // 1 + 7(padding) + 8 + 4 = 20 + 4 = 24

struct Three {
  struct One one;
  int c;
  char ch;
}; // 12 + 4 + 1 + 7(padding) = 24

struct Four {
  int c;
  struct One one; //12
  char ch;
}; // 4 + 4(padding) + 16 + 1 = 25 + 7 = 32


int main()
{
  // 16:24:24:32
  cout << sizeof(struct One) << ":" << sizeof(struct Two) << ":" << sizeof(struct Three) << ":" << sizeof(struct Four)<< endl;
}

