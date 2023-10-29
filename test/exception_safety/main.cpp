#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "utils /none_default_constructible.h"
#include "utils /throwing_default_constructor.h"
#include "vec.h"

TEST(ITERATOR, TEST1) {
    EXPECT_THROW(std::vector<throwing_default_constructor> v(2);, std::runtime_error);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
