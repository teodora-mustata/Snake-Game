#pragma once
#include "SnakeEvents.h"

class IObserverSnake {
public:
    virtual void update(SnakeEvent event) = 0;
    virtual ~IObserverSnake() = default;
};
