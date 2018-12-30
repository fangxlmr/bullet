#include <stdio.h>
#include <gtest/gtest.h>
#include "vector.h"
#include "stack.h"
#include "queue.h"

static int a[] = {
    11, 23, 35, 20, 
    2, -10, 330, -501,
    0, 0, 25, 78
};
int LEN = sizeof(a) / sizeof(a[0]);

TEST(vector, testing_vector)
{
    int i;
    vectorElem x;
    vector_t vector;

    ASSERT_EQ(0, vector_new(&vector));
    for (i = 0; i < LEN; i++) {
        EXPECT_EQ(0, vector_append(vector, &a[i]));
    }

    EXPECT_EQ(0, vector_append(vector, &a[2]));
    EXPECT_EQ(0, vector_pop(vector, &x));

    EXPECT_EQ(LEN, vector_get_size(vector));

    for (i = 0; i < LEN; i++) {
        EXPECT_EQ(0, vector_get(vector, i, &x));
        EXPECT_EQ(a[i], *(int *)x);
    }

    EXPECT_EQ(0, vector_set(vector, 2, &a[1]));
    EXPECT_EQ(0, vector_set(vector, 0, &a[2]));
    EXPECT_EQ(-1, vector_set(vector, 15, &a[3]));

    EXPECT_FALSE(vector_isempty(vector));

    for (i = 0; i < LEN; i++) {
        EXPECT_EQ(0, vector_pop(vector, &x));
    }

    EXPECT_TRUE(vector_isempty(vector));
    vector_free(&vector);
}

TEST(stack, stack_testing) {
    int i;
    stackElem x;
    _stack_t stack;

    ASSERT_EQ(0, stack_new(&stack));
    for (i = 0; i < LEN; i++) {
        EXPECT_EQ(0, stack_push(stack, &a[i]));
    }

    EXPECT_EQ(0, stack_pop(stack, &x));
    EXPECT_EQ(0, stack_push(stack, &a[2]));
    EXPECT_EQ(0, stack_peek(stack, &x));
    EXPECT_EQ(a[2], *(int *) x);

    EXPECT_EQ(LEN, stack_get_size(stack));
    EXPECT_FALSE(stack_isempty(stack));

    for (i = 0; i < LEN; i++) {
        EXPECT_EQ(0, stack_pop(stack, &x));
    }

    EXPECT_EQ(-1, stack_pop(stack, &x));
    EXPECT_EQ(-1, stack_peek(stack, &x));
    EXPECT_TRUE(stack_isempty(stack));
    stack_free(&stack);
}

TEST(queue, queue_testing) {
    int i;
    queueElem x;
    queue_t queue;

    ASSERT_EQ(0, queue_new(&queue));
    for (i = 0; i < LEN; i++) {
        EXPECT_EQ(0, queue_push(queue, &a[i]));
    }

    EXPECT_EQ(0, queue_pop(queue, &x));
    EXPECT_EQ(0, queue_push(queue, &a[2]));
    EXPECT_EQ(0, queue_peek(queue, &x));
    EXPECT_EQ(a[1], *(int *) x);

    EXPECT_EQ(LEN, queue_get_size(queue));
    EXPECT_FALSE(queue_isempty(queue));

    for (i = 0; i < LEN; i++) {
        EXPECT_EQ(0, queue_pop(queue, &x));
    }

    EXPECT_EQ(-1, queue_pop(queue, &x));
    EXPECT_EQ(-1, queue_peek(queue, &x));
    EXPECT_TRUE(queue_isempty(queue));
    queue_free(&queue);
}
int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
