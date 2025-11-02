#pragma once
#include "IObserverMap.h"

class ISubjectMap {
public:
    virtual void attach(IObserverMap* obs) = 0;
    virtual void detach(IObserverMap* obs) = 0;
    virtual void notify(MapEvent event, int x, int y) = 0;
    virtual ~ISubjectMap() = default;
};
