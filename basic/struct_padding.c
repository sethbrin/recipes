#include <iostream>

using namespace std;

#pragma pack(8)

struct One {
  double d;
  char c;
  int i;
};

struct Two {
  char c;
  double d;
  int i;
};

int main()
{
  cout << sizeof(struct One) << ":" << sizeof(struct Two) << endl;
}

