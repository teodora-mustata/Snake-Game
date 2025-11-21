
#include "GameController.h"
#include <random>
#include <ctime>
#include <algorithm>

GameController::GameController(Map& m, Snake& s, Score& sc)
    : map(m), snake(s), score(sc)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    scheduleNextSpawnSec();
}
void GameController::increaseDifficulty() {
    difficultyLevel++;

    //moveInterval = std::max(0.05, moveInterval - 0.03);
    moveInterval = std::max(0.12, moveInterval - 0.05);
    if (maxFruits < 5)
        maxFruits++;

     nextSpawnSec = std::max(1, nextSpawnSec - 1);
}

void GameController::scheduleNextSpawnSec() {
    nextSpawnSec = 1 + std::rand() % 10;
}

static std::pair<int, int> getRandomFreePosition(const Map& map, const Snake& snake) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(0, map.getWidth() - 1);
    std::uniform_int_distribution<> distY(0, map.getHeight() - 1);

    auto center = map.getCenterPosition();
    while (true) {
        int x = distX(gen);
        int y = distY(gen);

        if (x == center.first && y == center.second)
            continue;

        bool onSnake = false;
        for (auto& part : snake.getBody()) {
            if (part.first == x && part.second == y) {
                onSnake = true;
                break;
            }
        }
        if (!onSnake && !map.hasFruit(x, y))
            return { x, y };
    }
}

void GameController::initialize() {
    auto pos = getRandomFreePosition(map, snake);
    map.spawnFruit(pos.first, pos.second);
}

//void GameController::update(double deltaTime) {
//    elapsed += deltaTime;
//    if (elapsed >= nextSpawnSec) {
//        if ((int)map.getFruits().size() < maxFruits) {
//            auto pos = getRandomFreePosition(map, snake);
//            map.spawnFruit(pos.first, pos.second);
//        }
//        elapsed = 0.0;
//        scheduleNextSpawnSec();
//    }
//
//    moveElapsed += deltaTime;
//    while (moveElapsed >= moveInterval) {
//        snake.move(map);
//        moveElapsed -= moveInterval;
//    }
//}


void GameController::update(double deltaTime) {
    totalTime += deltaTime;
    if (nextDifficultyIndex < (int)difficultySteps.size() &&
        totalTime >= difficultySteps[nextDifficultyIndex]) {
        increaseDifficulty();
        nextDifficultyIndex++;
    }

    elapsed += deltaTime;
    if (elapsed >= nextSpawnSec) {
        if ((int)map.getFruits().size() < maxFruits) {
            auto pos = getRandomFreePosition(map, snake);
            map.spawnFruit(pos.first, pos.second);
        }
        elapsed = 0.0;
        scheduleNextSpawnSec();
    }

    moveElapsed += deltaTime;
    while (moveElapsed >= moveInterval) {
        snake.move(map);
        moveElapsed -= moveInterval;
    }
}
