#pragma once
#include <utility>
#include "Map.h"

class GameController {
private:
    Map& map;
    double elapsed = 0.0;
    int nextSpawnSec = 0;

    void scheduleNextSpawnSec();

public:
    explicit GameController(Map& m);

    void initializeMap();

    void updateMap(double deltaTime);

    std::pair<int, int> getSnakeSpawnPosition() const;
};