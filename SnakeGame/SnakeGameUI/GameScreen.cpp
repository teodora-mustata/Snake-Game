#include "GameScreen.h"
#include "GameFactory.h"
#include <QKeyEvent>

GameScreen::GameScreen(QWidget* parent)
    : QWidget(parent)
{
    gameApi = createGameAPI();
    snakeWidget = new SnakeWidget(gameApi.get(), this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(snakeWidget);

    connect(snakeWidget, &SnakeWidget::gameOverSignal, this, &GameScreen::gameOver);
    connect(snakeWidget, &SnakeWidget::restartSignal, this, &GameScreen::restartGame);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, [this]() {
        gameApi->update(0.2);
        });
}

void GameScreen::start()
{
    gameApi->initialize();
    gameTimer->start(200);
}

void GameScreen::gameOver() {
    gameTimer->stop();
    emit gameFinished();
}

void GameScreen::restartGame() {
    gameApi = createGameAPI();
    snakeWidget->reset(gameApi.get());
    start();
}

void GameScreen::keyPress(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W: gameApi->setSnakeDirection(Direction::Up); break;
    case Qt::Key_S: gameApi->setSnakeDirection(Direction::Down); break;
    case Qt::Key_A: gameApi->setSnakeDirection(Direction::Left); break;
    case Qt::Key_D: gameApi->setSnakeDirection(Direction::Right); break;
    }
}
