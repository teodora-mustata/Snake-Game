#include "GameAPI.h"

GameAPI::GameAPI()
    : map(20, 20),
    snake(10, 10),
    score(),
    controller(map, snake, score)
{
    snake.attach(&score);

}

void GameAPI::attachMapObserver(IObserverMap* obs) {
    map.attach(obs);
}

void GameAPI::attachSnakeObserver(IObserverSnake* obs) {
    snake.attach(obs);
}

void GameAPI::initialize() {
    controller.initialize();
}

void GameAPI::update(double deltaTime) {
    controller.update(deltaTime);
}

void GameAPI::setSnakeDirection(Direction dir) {
    snake.setDirection(dir);
}

std::vector<std::pair<int, int>> GameAPI::getFruits() const {
    return map.getFruits();
}

std::vector<std::pair<int, int>> GameAPI::getSnakeBody() const {
    return snake.getBody();
}

int GameAPI::getScore() const {
    return score.getPoints();
}
