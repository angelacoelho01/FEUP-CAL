#include "exercises.h"
#include <algorithm>
#include <iostream>

void printResult(bool result, unsigned int usedCoins[], unsigned int n){
    std::cout << "result = " << result << ", change = [ ";
    for(unsigned int i = 0; i < n; i++)
        std::cout << usedCoins[i] << " ";
    std::cout << "]" << std::endl << std::endl;
}

bool changeMaking(unsigned  int Coins[], unsigned int numCoins, unsigned int T, unsigned  int usedCoins[], unsigned int i){
    if(T == 0) return true;

    if(T < 0) return false;

    if(i == numCoins) return false;

    if (Coins[i] <= T) {
        usedCoins[i]++;
        if (changeMaking(Coins, numCoins, T - Coins[i], usedCoins, i + 1)) return true;

        usedCoins[i]--;
        if (changeMaking(Coins, numCoins, T, usedCoins, i + 1)) return true;
    }

    return false;
}

bool changeMakingBacktracking(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int numCoins = 0;
    for(int j = 0; j < n; j++) {
        usedCoins[j] = 0;
        numCoins += Stock[j];
    }

    unsigned int Coins[numCoins], usedCoins1[numCoins];
    unsigned count = 0;

    for(unsigned int j = 0; j < n; j++){
        for(unsigned int k = 0; k < Stock[j]; k++) {
            Coins[count] = C[j];
            usedCoins1[count++] = 0;
        }
    }
    bool result = changeMaking(Coins, numCoins, T, usedCoins1, 0);

    count = 0;
    for(unsigned int j = 0; j < n; j++){
        for(unsigned int k = 0; k < Stock[j]; k++) {
            usedCoins[j] += usedCoins1[count++];
        }
    }

    printResult(result, usedCoins, n);

    return result;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBacktracking(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,1,usedCoins), false);
}