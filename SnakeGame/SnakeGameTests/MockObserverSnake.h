#pragma once
#include "IObserverSnake.h"
#include <gmock/gmock.h>


class MockObserverSnake : public IObserverSnake {
public:
    MOCK_METHOD(void, update, (SnakeEvent event), (override));
};
