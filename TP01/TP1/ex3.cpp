#include "exercises.h"

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned minNumberCoins = INT_MAX;

    if (n == 4) {
        for (unsigned i = 0; i <= Stock[0]; i++) {
            for (unsigned j = 0; j <= Stock[1]; j++) {
                for (unsigned k = 0; k <= Stock[2]; k++) {
                    for (unsigned l = 0; l <= Stock[3]; l++) {
                        if (((C[0] * i + C[1] * j + C[2] * k + C[3] * l) == T) && (i + j + k + l < minNumberCoins)) {
                            usedCoins[0] = i;
                            usedCoins[1] = j;
                            usedCoins[2] = k;
                            usedCoins[3] = l;
                            return true;
                        }
                    }
                }
            }
        }
    }
    else if(n == 3){
        for (unsigned i = 0; i <= Stock[0]; i++) {
            for (unsigned j = 0; j <= Stock[1]; j++) {
                for (unsigned k = 0; k <= Stock[2]; k++) {
                    if (((C[0] * i + C[1] * j + C[2] * k) == T) && (i + j + k < minNumberCoins)) {
                        usedCoins[0] = i;
                        usedCoins[1] = j;
                        usedCoins[2] = k;
                        return true;
                    }
                }
            }
        }
    }

    return false;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP1_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP1_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}