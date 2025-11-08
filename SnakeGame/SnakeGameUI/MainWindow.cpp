#include "MainWindow.h"
#include "GameController.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    Map* map = new Map(20, 20);
    Snake* snake = new Snake(10, 10);
    Score* score = new Score();

    GameController* controller = new GameController(*map, *snake, *score);
    controller->initialize();

    SnakeWidget* snakeWidget = new SnakeWidget(*map, *snake, *controller, this);

    setCentralWidget(snakeWidget);
    resize(400, 400);
}
