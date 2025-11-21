
#pragma once
#include "EnumEvents.h"
#include "IObserverMap.h"
#include "IObserverSnake.h"
#include <vector>
#include <utility>

class IGameAPI {
public:
    virtual void attachMapObserver(IObserverMap* obs) = 0;
    virtual void attachSnakeObserver(IObserverSnake* obs) = 0;

    virtual void initialize() = 0;
    virtual void update(double deltaTime) = 0;
    virtual void setSnakeDirection(Direction dir) = 0;

    virtual std::vector<std::pair<int, int>> getFruits() const = 0;
    virtual std::vector<std::pair<int, int>> getSnakeBody() const = 0;
    virtual int getScore() const = 0;
    virtual double getElapsedTime() const = 0;


    virtual ~IGameAPI() = default;
};
