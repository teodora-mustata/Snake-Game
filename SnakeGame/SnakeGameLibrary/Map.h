#pragma once
#include <vector>
#include <utility>   
#include "ISubjectMap.h"
#include "IObserverMap.h"

class Map : public ISubjectMap {
private:
    int width;
    int height;

    std::vector<std::pair<int, int>> fruits;

    std::vector<IObserverMap*> observers;

public:
    Map(int w, int h);

    int getWidth()  const;
    int getHeight() const;

    std::pair<int, int> getCenterPosition() const;

    void attach(IObserverMap* obs) override;
    void detach(IObserverMap* obs) override;
    void notify(MapEvent event, int x, int y) override;

    bool isInside(int x, int y) const;
    bool hasFruit(int x, int y) const;
    bool hasAnyFruit() const;      

    std::vector<std::pair<int, int>> getFruits() const;

    void spawnFruit(int x, int y);  
    void removeFruit(int x, int y); 
};

