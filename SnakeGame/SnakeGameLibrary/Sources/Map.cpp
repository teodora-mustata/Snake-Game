#include "Map.h"
#include <algorithm>

void Map::attach(IObserverMap* obs) {
    observers.push_back(obs);
}

void Map::detach(IObserverMap* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Map::notify(MapEvent event, int x, int y) {
    for (auto obs : observers)
        obs->update(event, x, y);
}

void Map::spawnFruit(int x, int y) {
    // logica plasare fruct
    notify(MapEvent::FruitAppeared, x, y);
}

void Map::removeFruit(int x, int y) {
    // ...
    notify(MapEvent::FruitRemoved, x, y);
}
