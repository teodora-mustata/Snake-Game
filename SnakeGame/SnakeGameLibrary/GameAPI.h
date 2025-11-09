#pragma once
#include "IGameAPI.h"
#include "Map.h"
#include "Snake.h"
#include "Score.h"
#include "GameController.h"

class GameAPI : public IGameAPI {
private:
    Map map;
    Snake snake;
    Score score;
    GameController controller;

public:
    GameAPI();

    void attachMapObserver(IObserverMap* obs) override;
    void attachSnakeObserver(IObserverSnake* obs) override;

    void initialize() override;
    void update(double deltaTime) override;
    void setSnakeDirection(Direction dir) override;

    std::vector<std::pair<int, int>> getFruits() const override;
    std::vector<std::pair<int, int>> getSnakeBody() const override;
};

