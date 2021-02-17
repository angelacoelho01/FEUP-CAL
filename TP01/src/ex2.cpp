#include "exercises.h"

int sumArray(const int A[], unsigned i, unsigned j){
    int sum = 0;
    for(; i <= j; i++)
        sum += A[i];
    return sum;
}

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int maxSum = 0, sum = INT_MIN;
    unsigned k = 0, l = 0;

    for(; k <= l && k <= n; k++, n--){
        for(l = k+1; k <= l && l <= n; l++){
            sum = sumArray(A, k, l);
            if(sum > maxSum){
                maxSum = sum;
                i = k;
                j = l;
            }
        }
    }

    return maxSum;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex2, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}