#include "common.h"

#ifdef TEST1

testing::AssertionResult IsEven(int n) {
    if ((n % 2) == 0)
        return testing::AssertionSuccess();
    else
        return testing::AssertionFailure() << n << " is odd";
}

int Factorial(int n)  // Returns the factorial of n
{
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Tests factorial of 0.
TEST(FactorialTest, HandlesZeroInput) {
    EXPECT_EQ(Factorial(0), 1);
}

// Tests factorial of positive numbers.
TEST(FactorialTest, HandlesPositiveInput) {
    EXPECT_EQ(Factorial(1), 1);
    EXPECT_EQ(Factorial(2), 2);
    EXPECT_EQ(Factorial(3), 6);
    EXPECT_EQ(Factorial(8), 40320);
}

TEST(FactorialIsEvenTest, AssertionResult) {
    EXPECT_TRUE(IsEven(Factorial(3)));
}

#endif