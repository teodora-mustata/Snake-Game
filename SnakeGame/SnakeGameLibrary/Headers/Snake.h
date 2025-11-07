#pragma once
#include <vector>
#include "ISubjectSnake.h"
#include "IObserverSnake.h"
#include "EnumEvents.h"


class Snake : public ISubjectSnake {
private:
    std::vector<IObserverSnake*> observers;
    // restul detaliilor despre sarpe gen lungime, pozitie, directie etc.

    std::vector<std::pair<int, int>> body;
    Direction direction;
    bool alive;
public:
    Snake(int startX = 0, int startY = 0);


    void attach(IObserverSnake* obs) override;
    void detach(IObserverSnake* obs) override;
    void notify(SnakeEvent event) override;

    void move();
    void eatFruit();
    void hitWall();
    void hitSelf();

    void setDirection(Direction newDir);
    std::pair<int, int> getHeadPosition() const;
    const std::vector<std::pair<int, int>>& getBody() const;

    bool isAlive() const { return alive; }
};
