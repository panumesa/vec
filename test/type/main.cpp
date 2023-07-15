#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "utils /none_default_constructible.h"
#include "vec.h"
TEST(TYPE, TEST1) { std::vector<none_default_constructible> a; }
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
