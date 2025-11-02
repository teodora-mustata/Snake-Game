#pragma once
#include "SnakeEvents.h"

class IObserverMap {
public:
    virtual void update(MapEvent event, int x, int y) = 0;
    virtual ~IObserverMap() = default;
};
