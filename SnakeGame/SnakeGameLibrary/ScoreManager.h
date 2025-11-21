#pragma once
#include <vector>
#include <utility>
#include <string>

class ScoreManager {
public:
    static void saveScore(int score, double time);
    static std::vector<std::pair<int, double>> loadScores();
};