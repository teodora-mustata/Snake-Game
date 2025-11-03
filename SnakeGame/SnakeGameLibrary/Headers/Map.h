//#pragma once
//#include <vector>
//#include "ISubjectMap.h"
//#include "IObserverMap.h"
//
//class Map : public ISubjectMap {
//private:
//    std::vector<IObserverMap*> observers;
//    // restul detaliilor despre map gen dimensiuni, fructe etc.
//public:
//    void attach(IObserverMap* obs) override;
//    void detach(IObserverMap* obs) override;
//    void notify(MapEvent event, int x, int y) override;
//
//    void spawnFruit(int x, int y);
//    void removeFruit(int x, int y);
//};


#pragma once
#include <vector>
#include <utility>   // std::pair
#include "ISubjectMap.h"
#include "IObserverMap.h"

// Map = modelul de date pentru harta + emitent de evenimente.

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

    // —— Observer API ——
    void attach(IObserverMap* obs) override;
    void detach(IObserverMap* obs) override;
    void notify(MapEvent event, int x, int y) override;

    // —— API harta ——
    bool isInside(int x, int y) const;
    bool hasFruit(int x, int y) const;
    bool hasAnyFruit() const;      

    void spawnFruit(int x, int y);  
    void removeFruit(int x, int y); 
};

