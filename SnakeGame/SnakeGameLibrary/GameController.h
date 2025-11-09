#pragma once
#include "Map.h"
#include "Snake.h"
#include "Score.h"
#include <random>

class GameController {
private:
    Map& map;
    Snake& snake;
    Score& score;

    double elapsed = 0.0;
    int nextSpawnSec = 0;

    void scheduleNextSpawnSec();
public:
    GameController(Map& m, Snake& s, Score& sc);
    void initialize();
    void update(double deltaTime);
};
