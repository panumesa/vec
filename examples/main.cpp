#include <iostream>

#include "vec.h"
int main() {
  vec<int> brr;
  for (int i = 0; i < 5; ++i) {
    brr.push_back(i);
  }
  brr[0];
  for (int i = 0; i < 5; ++i) {
    std::cout << brr[i] << ' ';
  }
  for (int i = 0; i < 5; ++i) {
    brr.pop_back();
  }
  return 0;
}
