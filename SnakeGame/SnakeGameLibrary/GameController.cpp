#include <cstdlib>   
#include "GameController.h"

GameController::GameController(Map& m)
    : map(m) {}

void GameController::scheduleNextSpawnSec() {
    // 1..10 inclusiv
    nextSpawnSec = 1 + (std::rand() % 10);
}

void GameController::initializeMap() {
    elapsed = 0.0;
    scheduleNextSpawnSec();
}

void GameController::updateMap(double deltaTime) {
    if (map.hasAnyFruit()) return;

    elapsed += deltaTime;

    if (elapsed >= static_cast<double>(nextSpawnSec)) {
        int x = std::rand() % map.getWidth();
        int y = std::rand() % map.getHeight();

        map.spawnFruit(x, y);

        elapsed = 0.0;
        scheduleNextSpawnSec();
    }
}

std::pair<int, int> GameController::getSnakeSpawnPosition() const {
    return map.getCenterPosition();
}
