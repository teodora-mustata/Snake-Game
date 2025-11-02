#pragma once
#include <vector>
#include "ISubjectSnake.h"
#include "IObserverSnake.h"

class Snake : public ISubjectSnake {
private:
    std::vector<IObserverSnake*> observers;
    // restul detaliilor despre sarpe gen lungime, pozitie, directie etc.
public:
    void attach(IObserverSnake* obs) override;
    void detach(IObserverSnake* obs) override;
    void notify(SnakeEvent event) override;

    void move();
    void eatFruit();
    void hitWall();
    void hitSelf();
};
