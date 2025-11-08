#include "GameController.h"
#include <cstdlib>
#include <ctime>

GameController::GameController(Map& m, Snake& s, Score& sc)
    : map(m), snake(s), score(sc) {
    srand(static_cast<unsigned>(time(nullptr)));
    scheduleNextSpawnSec();
}

void GameController::scheduleNextSpawnSec() {
    nextSpawnSec = 1+ rand() % 10;
}

void GameController::initialize() {
    map.spawnFruit(map.getWidth() / 2, map.getHeight() / 2);
}

void GameController::update(double deltaTime) {
    elapsed += deltaTime;

    if (elapsed >= nextSpawnSec) {
        int x = rand() % map.getWidth();
        int y = rand() % map.getHeight();
        map.spawnFruit(x, y);
        elapsed = 0.0;
        scheduleNextSpawnSec();
    }

    snake.move(map);
}
