#pragma once
#include <vector>
#include "ISubjectMap.h"
#include "IObserverMap.h"

class Map : public ISubjectMap {
private:
    std::vector<IObserverMap*> observers;
    // restul detaliilor despre map gen dimensiuni, fructe etc.
public:
    void attach(IObserverMap* obs) override;
    void detach(IObserverMap* obs) override;
    void notify(MapEvent event, int x, int y) override;

    void spawnFruit(int x, int y);
    void removeFruit(int x, int y);
};
