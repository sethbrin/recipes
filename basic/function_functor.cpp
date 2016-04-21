//
// test the speed of functor and function
// Author: Ping Zeng(zengping10212044@gmail.com)
//
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ctime>

using std::vector;
using std::cout;
using std::endl;
using std::greater;

#include "../util/util.h"

bool cmp(const double lhs, const double rhs)
{
  return lhs > rhs;
}

int main()
{
  double d;
  double time_used;

  vector<int> vec;
  srand(time(NULL));
  generate_n(back_inserter(vec), 10000000, rand);
  vector<int> vec2;
  copy(vec.begin(), vec.end(), back_inserter(vec2));

  // functor: 5.70156s
  // function: 5.88186s
  d = realtime();
  sort(vec.begin(), vec.end(), greater<int>());
  time_used = realtime() - d;
  cout << "functor: " << time_used << "s" << endl;

  d = realtime();
  sort(vec2.begin(), vec2.end(), cmp);
  time_used = realtime() - d;
  cout << "function: " << time_used << "s" << endl;
}
