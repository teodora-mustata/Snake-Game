#include "Score.h"

Score::Score() : points(0) {}

void Score::update(SnakeEvent event) {
    if (event == SnakeEvent::AteFruit)
        points += 10; // TO DO: valoare diferita pentru tipuri diferite de fructe?
}

int Score::getPoints() const {
    return points;
}
