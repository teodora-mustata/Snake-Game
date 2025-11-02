#pragma once
#include "IObserverSnake.h"

class ISubjectSnake {
public:
    virtual void attach(IObserverSnake* obs) = 0;
    virtual void detach(IObserverSnake* obs) = 0;
    virtual void notify(SnakeEvent event) = 0;
    virtual ~ISubjectSnake() = default;
};
