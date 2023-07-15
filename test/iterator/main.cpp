#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "utils /none_default_constructible.h"
#include "vec.h"
TEST(ITERATOR, TEST1) {
  std::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int>::iterator p = v.begin() + 3;
  ASSERT_EQ(4, *p);
}
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
