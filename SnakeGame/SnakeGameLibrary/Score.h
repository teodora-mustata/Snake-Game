#pragma once
#include "IObserverSnake.h"

class Score : public IObserverSnake {
private:
    int points;
public:
    Score();
    void update(SnakeEvent event) override;
    int getPoints() const;
};
