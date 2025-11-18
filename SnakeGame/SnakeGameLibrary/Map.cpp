

#include <algorithm>
#include "Map.h"

Map::Map(int w, int h)
    : width(w), height(h) {}

int Map::getWidth()  const { return width; }
int Map::getHeight() const { return height; }

std::pair<int, int> Map::getCenterPosition() const {
    return { width / 2, height / 2 };
}

void Map::attach(IObserverMap* obs) {
    observers.push_back(obs);
}

void Map::detach(IObserverMap* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Map::notify(MapEvent event, int x, int y) {
    for (auto* obs : observers) {
        if (obs)
            obs->update(event, x, y);
    }
}

bool Map::isInside(int x, int y) const {
    return x >= 0 && y >= 0 && x < width && y < height;
}

bool Map::hasFruit(int x, int y) const {
    for (const auto& f : fruits) {
        if (f.first == x && f.second == y) return true;
    }
    return false;
}

bool Map::hasAnyFruit() const {
    return !fruits.empty();
}

std::vector<std::pair<int, int>> Map::getFruits() const {
    return fruits;
}

void Map::spawnFruit(int x, int y) {
    if (!isInside(x, y)) return;

    fruits.emplace_back(x, y);
    notify(MapEvent::FruitSpawned, x, y);
}

void Map::removeFruit(int x, int y) {
    auto it = std::remove_if(fruits.begin(), fruits.end(),
        [x, y](const std::pair<int, int>& f) { return f.first == x && f.second == y; });

    if (it != fruits.end()) {
        fruits.erase(it, fruits.end());
        notify(MapEvent::FruitRemoved, x, y);
    }
}
