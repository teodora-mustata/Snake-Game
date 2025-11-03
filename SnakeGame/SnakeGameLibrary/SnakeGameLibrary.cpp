//#include <iostream>
//#include "Headers/Score.h"
//#include "Headers/Snake.h"
//
//int main() {
//    Snake snake;
//    Score score;
//
//    // atașăm observer-ul
//    snake.attach(&score);
//
//    // simulăm evenimente
//    snake.move();
//    snake.eatFruit();
//    snake.eatFruit();
//    snake.hitWall();
//
//    std::cout << "Scorul curent: " << score.getPoints() << "\n";
//
//    return 0;
//}


#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Headers/Map.h"
#include "GameController.h"

class ConsoleMapObserver : public IObserverMap {
public:
    void update(MapEvent event, int x, int y) override {
        if (event == MapEvent::FruitAppeared)
            std::cout << "[EVENT] Fruit appeared at (" << x << ", " << y << ")\n";
        else if (event == MapEvent::FruitRemoved)
            std::cout << "[EVENT] Fruit removed at (" << x << ", " << y << ")\n";
    }
};

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Map map(10, 10);
    ConsoleMapObserver obs;
    map.attach(&obs);

    GameController ctrl(map);
    ctrl.initializeMap();

    for (int sec = 1; sec <= 60; ++sec) {
        ctrl.updateMap(1.0);

        std::cout << "[Time] second " << sec << "\n";

    }

    return 0;
}

