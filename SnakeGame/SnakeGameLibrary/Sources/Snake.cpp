#include <algorithm>
#include "../Headers/IObserverSnake.h"
#include "../Headers/Map.h"
#include "../Headers/Snake.h"


Snake::Snake(int startX, int startY)
    : direction(Direction::Right), alive(true)
{
    body.push_back({ startX, startY });
}


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


void Snake::setDirection(Direction newDir) {

    if ((direction == Direction::Up && newDir == Direction::Down) ||
        (direction == Direction::Down && newDir == Direction::Up) ||
        (direction == Direction::Left && newDir == Direction::Right) ||
        (direction == Direction::Right && newDir == Direction::Left))
        return;

    direction = newDir;
}

void Snake::move(Map& map) {
    if (!alive) return;
    std::pair<int, int> head = body.front();
    int headX = head.first;
    int headY = head.second;
    switch (direction) {
    case Direction::Up: headY--; break;
    case Direction::Down: headY++; break;
    case Direction::Left: headX--; break;
    case Direction::Right: headX++; break;
    }

    if (!map.isInside(headX, headY)) {
        hitWall();
        return;
    }

    for (auto& part : body) {
        if (part.first == headX && part.second == headY) {
            hitSelf();
            return;
        }
    }

    if (map.hasFruit(headX, headY)) {
        eatFruit();
        map.removeFruit(headX, headY);
    }
    else {
        body.pop_back();
    }

    body.insert(body.begin(), { headX, headY });

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
    notify(SnakeEvent::HitSelf);

}
//
//std::pair<int, int> Snake::getHeadPosition() const {
//    return body.front();
//}

const std::vector<std::pair<int, int>>& Snake::getBody() const {
    return body;
}