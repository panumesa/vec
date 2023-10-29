#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "utils /none_default_constructible.h"
#include "vec.h"

TEST(SACCESS, TEST1) {
    vec<int> a;
    a.push_back(1);
    EXPECT_EQ(a[0], 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
