#pragma once
#include <vector>
#include "ISubjectSnake.h"
#include "IObserverSnake.h"
#include "EnumEvents.h"
#include "Map.h"



class Snake : public ISubjectSnake {
private:
    std::vector<IObserverSnake*> observers;

    std::vector<std::pair<int, int>> body;
    Direction direction;
    Direction nextDirection;
    bool alive;

public:
    Snake(int startX = 0, int startY = 0);

    void attach(IObserverSnake* obs) override;
    void detach(IObserverSnake* obs) override;
    void notify(SnakeEvent event) override;

    void move(Map& map);
    void eatFruit();
    void hitWall();
    void hitSelf();

    void setDirection(Direction newDir);
    const std::vector<std::pair<int, int>>& getBody() const;

    bool isAlive() const { return alive; }
};
