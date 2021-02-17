#include "exercises.h"

bool isCanonical(unsigned int C[], unsigned int n) {
    unsigned a = C[2] + 1;
    unsigned b = C[n-2] + C[n-1];
    unsigned int* usedCoins1 = new unsigned int[n];
    unsigned int* usedCoins2 = new unsigned int[n];
    unsigned int* stock = new unsigned int[n];

    for(unsigned i = 0; i < n; i++)
        stock[i] = 1;

    for(unsigned i = a + 1; i < b; i++) {
        changeMakingBF(C, stock, n, i, usedCoins1);
        changeMakingGreedy(C, stock, n, i, usedCoins2);
        if(std::memcmp(usedCoins1, usedCoins2, sizeof(*usedCoins1)) != 0)
            return false;
    }
    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, canonicalTrue) {
    unsigned int C[] = {1,2,5};
    EXPECT_EQ(isCanonical(C,3), true);

    unsigned int C2[] = {1,2,5,10};
    EXPECT_EQ(isCanonical(C2,4), true);
}

TEST(TP1_Ex5, canonicalFalse) {
    unsigned int C[] = {1,4,5};
    EXPECT_EQ(isCanonical(C,3), false);
}