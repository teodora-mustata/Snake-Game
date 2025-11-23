#include "pch.h"
#include <gtest/gtest.h>

#include "ScoreManager.h"

TEST(ScoreManagerTests, SaveAndLoadScoresWorks) {
    
    std::remove("best_scores.txt");
    ScoreManager::saveScore(50, 10.5);
    auto scores = ScoreManager::loadScores();

    ASSERT_FALSE(scores.empty());
    EXPECT_EQ(scores.front().first, 50);
}
