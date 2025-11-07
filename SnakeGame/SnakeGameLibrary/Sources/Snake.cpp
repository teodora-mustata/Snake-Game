#include <algorithm>
#include "../Headers/IObserverSnake.h"
#include "../Headers/Map.h"
#include "../Headers/Snake.h"


Snake::Snake(int startX, int startY)
    : direction(Direction::Right), alive(true)
{
    body.push_back({ startX, startY });
}

//observer
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

//logica
void Snake::setDirection(Direction newDir) {

    if ((direction == Direction::Up && newDir == Direction::Down) ||
        (direction == Direction::Down && newDir == Direction::Up) ||
        (direction == Direction::Left && newDir == Direction::Right) ||
        (direction == Direction::Right && newDir == Direction::Left))
        return;

    direction = newDir;
}

void Snake::move() {
    
    if (!alive) return;

    std::pair<int, int> newHead = body.front();

    switch (direction) {
    case Direction::Up:    newHead.second--; break;
    case Direction::Down:  newHead.second++; break;
    case Direction::Left:  newHead.first--;  break;
    case Direction::Right: newHead.first++;  break;
    }

    body.insert(body.begin(), newHead);

    body.pop_back();

    notify(SnakeEvent::Move);
}



void Snake::eatFruit() {

    if (!alive) return;
    body.push_back(body.back());

    notify(SnakeEvent::AteFruit);
}

void Snake::hitWall() {
    alive = false;

    notify(SnakeEvent::HitWall);
}

void Snake::hitSelf()
{
    alive = false;
    //trebuie notify

}

std::pair<int, int> Snake::getHeadPosition() const {
    return body.front();
}

const std::vector<std::pair<int, int>>& Snake::getBody() const {
    return body;
}

