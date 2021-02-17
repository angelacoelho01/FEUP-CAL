#include "exercises.h"
#include <algorithm>
#include <vector>
#include <numeric>

double minimumAverageCompletionTime(std::vector<unsigned int> tasks, std::vector<unsigned int> &orderedTasks) {
    for(const auto& task : tasks)
        orderedTasks.push_back(task);
    std::sort(orderedTasks.begin(), orderedTasks.end(), [](const unsigned int& rhs, const unsigned int& lhs){
        return rhs < lhs;
    });

    std::vector<int> tmp;
    for(const auto& task : orderedTasks)
        tmp.push_back(task);

    unsigned sum = 0;
    for(unsigned i = 0; i < tasks.size(); i++){
        sum += tmp[i];
        tmp[i] = sum;
    }

    return ((double)std::accumulate(tmp.begin(), tmp.end(), 0))/tmp.size();

}


/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex7, taskOrdering) {
    std::vector<unsigned int> tasks = {15, 8, 3, 10};
    std::vector<unsigned int> orderedTasks;
    double averageTime = minimumAverageCompletionTime(tasks, orderedTasks);
    EXPECT_EQ(orderedTasks.size(), 4 );
    ASSERT_NEAR(averageTime, 17.75, 0.00001);
    ASSERT_THAT(orderedTasks,  ::testing::ElementsAre(3,8,10,15));
}