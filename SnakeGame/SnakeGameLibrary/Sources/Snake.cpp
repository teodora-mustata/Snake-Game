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

    std::pair<int, int> newHead = body.front();

    switch (direction) {
    case Direction::Up:    newHead.second--; break;
    case Direction::Down:  newHead.second++; break;
    case Direction::Left:  newHead.first--;  break;
    case Direction::Right: newHead.first++;  break;
    }

    body.insert(body.begin(), newHead);

    body.pop_back();

    checkCollisions(map);

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
//
//const std::vector<std::pair<int, int>>& Snake::getBody() const {
//    return body;
//}

void Snake::checkCollisions(Map& map) {
    if (!alive) return;

    auto head = body.front();

   
    if (head.first < 0 || head.second < 0 ||
        head.first >= map.getWidth() || head.second >= map.getHeight()) {
        hitWall();
        return;
    }

    
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i] == head) {
            hitSelf();
            return;
        }
    }

    /*if (map.hasFruitAt(head.first, head.second)) {
        eatFruit();
        map.removeFruit(head.first, head.second);
    }*/
}
