#include "EnumEvents.h"
#include "Score.h"



Score::Score() : points(0) {}

void Score::update(SnakeEvent event) {
    if (event == SnakeEvent::AteFruit)
        points += 10;
}

int Score::getPoints() const {
    return points;
}
