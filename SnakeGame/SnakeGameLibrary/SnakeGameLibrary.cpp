#include <iostream>
#include "Snake.h"
#include "Score.h"

int main() {
    Snake snake;
    Score score;

    // atașăm observer-ul
    snake.attach(&score);

    // simulăm evenimente
    snake.move();
    snake.eatFruit();
    snake.eatFruit();
    snake.hitWall();

    std::cout << "Scorul curent: " << score.getPoints() << "\n";

    return 0;
}
