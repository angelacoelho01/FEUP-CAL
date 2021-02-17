#include "exercises.h"

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned minNumberCoins = INT_MAX;
    bool possibleChange = false;

    unsigned* countCoin = new unsigned[n];
    unsigned nCombinations = 1;
    for(unsigned i = 0; i < n; i++){
        usedCoins[i] = 0;
        countCoin[i] = 0;
        nCombinations *= (Stock[i] + 1);
    }

    bool  next;

    for(unsigned i = 0; i < nCombinations - 1; i++){
        next = false;

        for(int j = (int) n - 1; j >= 0; j--){
            if(((countCoin[j] >= Stock[j]) && (j == n-1)) || (countCoin[j] > Stock[j])) {
                countCoin[j] = 0;
                countCoin[j - 1]++;
                next = true;
            }
        }

        if (!next) countCoin[n-1]++;

        unsigned amount = 0, nCoins = 0;
        for(unsigned j = 0; j < n; j++){
            nCoins += countCoin[j];
            amount += C[j]*countCoin[j];
        }

        if(amount == T && nCoins < minNumberCoins){
            for(unsigned j = 0; j < n; j++)
                usedCoins[j] = countCoin[j];
            minNumberCoins = nCoins;
            possibleChange = true;
        }

    }
    return possibleChange;
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