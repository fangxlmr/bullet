#include <stdio.h>
#include <gtest/gtest.h>
#include "vector.h"

static int a[3] = {1, 2, 3};
static vector_t vector;

TEST(vector, create_vector)
{
    ASSERT_EQ(0, vector_new(&vector));
}

TEST(vector, append_value)
{
    EXPECT_EQ(0, vector_append(vector, &a[0]));
    EXPECT_EQ(0, vector_append(vector, &a[1]));
    EXPECT_EQ(0, vector_append(vector, &a[2]));
}

TEST(vector, set_value)
{
    EXPECT_EQ(-1, vector_set(vector, 3, &a[2]));
    EXPECT_EQ(-1, vector_set(vector, 4, &a[2]));
}
int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
