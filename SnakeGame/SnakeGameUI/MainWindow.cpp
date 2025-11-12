
#include "MainWindow.h"
#include <QKeyEvent>
#include "GameFactory.h"

MainWindow::MainWindow(IGameAPI* api, QWidget* parent)
    : QMainWindow(parent), gameApi(api)
{

    snakeWidget = new SnakeWidget(gameApi, this);
    setCentralWidget(snakeWidget);
    resize(500, 500);

    connect(snakeWidget, &SnakeWidget::gameOverSignal, this, &MainWindow::gameOver);
    connect(snakeWidget, &SnakeWidget::restartSignal, this, &MainWindow::startGame);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, [this]() {
        gameApi->update(0.2);
        });

    gameApi->initialize();
    gameTimer->start(200);
}

void MainWindow::startGame() {
    delete gameApi;            
    gameApi = createGameAPI();  
    snakeWidget->reset(gameApi);
    connect(snakeWidget, &SnakeWidget::gameOverSignal, this, &MainWindow::gameOver);

    gameApi->initialize();
    gameTimer->start(200);
  
}

void MainWindow::gameOver() {
    gameTimer->stop();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W: gameApi->setSnakeDirection(Direction::Up); break;
    case Qt::Key_S: gameApi->setSnakeDirection(Direction::Down); break;
    case Qt::Key_A: gameApi->setSnakeDirection(Direction::Left); break;
    case Qt::Key_D: gameApi->setSnakeDirection(Direction::Right); break;
    }
}
