#include "ScoreManager.h"
#include <fstream>
#include <algorithm>

static const std::string FILE_NAME = "best_scores.txt";

std::vector<std::pair<int, double>> ScoreManager::loadScores() {
    std::vector<std::pair<int, double>> vec;

    std::ifstream in(FILE_NAME);
    if (!in.good()) return vec;

    int s;
    double t;

    while (in >> s >> t)
        vec.push_back({ s, t });

    std::sort(vec.begin(), vec.end(),
        [](auto& a, auto& b) { 
            if (a.first != b.first)
                return a.first > b.first;  
            return a.second > b.second; });

    if (vec.size() > 5)
        vec.resize(5);

    return vec;
}

void ScoreManager::saveScore(int score, double time) {
    auto scores = loadScores();

    scores.push_back({ score, time });

    std::sort(scores.begin(), scores.end(),
        [](auto& a, auto& b) { return a.first > b.first; });

    if (scores.size() > 5)
        scores.resize(5);

    std::ofstream out(FILE_NAME, std::ios::trunc);

    for (auto& pair : scores)
        out << pair.first << " " << pair.second << "\n";
}
