#include <iostream>
#include <set>
#include "vec.h"
int main() {
  vec<int> brr = {1,2,3,4,5};
  std::set<int> s = {7,6,5,1,2,3,4};
  vec<int> crr(s.crbegin(), s.crend());
//  for (int i = 0; i < 5; ++i) {
//    std::cout << brr[i] << ' ';
//  }
  for (int i = 0; i < crr.size(); ++i) {
    std::cout << crr[i] << ' ';
  }
  for (int i = 0; i < 5; ++i) {
    brr.pop_back();
  }

  return 0;
}
