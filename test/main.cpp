#include <iostream>
#include "vec.full.h"
void test1(){
    vec<int> a;
    a.push_back(1);
    if(a[0] != 1)
        throw std::runtime_error("test 1 failed!"); ;
}
void test2(){
    vec<int> a;
    a.push_back(1);
    if(a[0] != 0)
        throw std::runtime_error("test 2 failed!"); ;
}
int main() {
    test1();
    test2();
    return 0;
}
