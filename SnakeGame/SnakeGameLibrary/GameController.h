

#pragma once
#include "Map.h"
#include "Snake.h"
#include "Score.h"
#include <random>
#include <vector>

class GameController {
private:
    Map& map;
    Snake& snake;
    Score& score;

    double elapsed = 0.0;
    int nextSpawnSec = 0;

    double moveElapsed = 0.0;
    double moveInterval = 0.40;

    int maxFruits = 1;

    double totalTime = 0.0;
    int difficultyLevel = 0;
    std::vector<double> difficultySteps = { 30.0, 60.0, 100.0, 150.0, 210.0 };
    int nextDifficultyIndex = 0;

    void scheduleNextSpawnSec();
    void increaseDifficulty(); 

public:
    GameController(Map& m, Snake& s, Score& sc);
    void initialize();
    void update(double deltaTime);
};
