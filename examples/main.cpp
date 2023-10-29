#include <iostream>
#include <set>
#include <queue>
#include "vec.h"
#include "stack.h"
#include <ranges>
#include <list>
#include <deque>
#include <algorithm>

void example_erase() {
    vec<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
    a.erase(a.cbegin() + 1, a.cend());
    for (auto x: a) {
        std::cout << x << ' ';
    }
    std::cout << std::endl << a.capacity() << std::endl;
}

void example_stack() {
    stack<int, vec<int>> a;
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    for (int i = 0; i < 4; ++i) {
        std::cout << a.top() << ' ';
        a.pop();
    }
    std::cout << std::endl;

}

int main() {
    example_erase();
    example_stack();

    /*vec<int> a = {1,2,3,4,5,6};
    vec<int> b;
    vec<int> c = {5,2,1,3,4};
    std::priority_queue<int, vec<int>> q(a.cbegin(),a.cend());
    while(!q.empty()){
      std::cout << q.top() << ' ';
      q.pop();
    }
    std::cout << std::endl;
  //  vec<int> sa = {1,2,3,4,5,6};
  //  for (auto it: sa | std::ranges::views::filter([](int x)-> bool{
  //      return x&1;
  //  }) | std::ranges::views::transform([](int x)->int{
  //      return x*x;
  //  }) | std::ranges::views::take(2)) {
  //        std::cout << it << ' ';
  //  }
  //  std::cout << std::endl;

  //  std::transform(a.cbegin(),a.cend(), std::back_inserter(b),[](const int x){return -x*x;});
    b.resize(a.size());
    std::transform(a.cbegin(),a.cend(), b.begin(),[](const int x){return -x*x;});
    b.push_back(3);
  //  std::sort(b.rbegin(),b.rend(),std::less<int>());
    for (auto it : b) {
      std::cout << it << ' ';
    }
    return 0;
     */
}
//TODO std::span std::ranges std::reduce std::merge ,,, std::priority_queue