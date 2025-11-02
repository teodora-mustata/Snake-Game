#include "Snake.h"
#include <algorithm>

void Snake::attach(IObserverSnake* obs) {
    observers.push_back(obs);
}

void Snake::detach(IObserverSnake* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Snake::notify(SnakeEvent event) {
    for (auto obs : observers)
        obs->update(event);
}

void Snake::move() {
    // logica mutare sarpe
    notify(SnakeEvent::Move);
}

void Snake::eatFruit() {
    // creste sarpele si scorul
    notify(SnakeEvent::AteFruit);
}

void Snake::hitWall() {
    notify(SnakeEvent::HitWall);
}

void Snake::hitWall() {
    notify(SnakeEvent::HitSelf);
}
