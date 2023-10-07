#include <iostream>
#include <set>
#include <queue>
#include "vec.h"
#include <algorithm>
int main() {
  vec<int> a = {1,2,3,4,5,6};
  vec<int> b;
  vec<int> c = {5,2,1,3,4};
//  std::priority_queue<int, vec<int>> q(a.cbegin(),a.cend());
//  while(!q.empty()){
//    std::cout << q.top() << ' ';
//    q.pop();
//  } TODO
//  std::transform(a.cbegin(),a.cend(), std::back_inserter(b),[](const int x){return -x*x;});
  b.resize(a.size());
  std::transform(a.cbegin(),a.cend(), b.begin(),[](const int x){return -x*x;});
  b.push_back(3);
  std::sort(b.rbegin(),b.rend(),std::less<int>());
  for (auto it : b) {
    std::cout << it << ' ';
  }
  return 0;
}
//TODO std::span std::ranges std::reduce std::merge ,,, std::priority_queue