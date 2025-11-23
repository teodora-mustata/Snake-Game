#pragma once
#include "IObserverMap.h"
#include <gmock/gmock.h>

class MockObserverMap : public IObserverMap {
public:
    MOCK_METHOD(void, update, (MapEvent event, int x, int y), (override));
};
