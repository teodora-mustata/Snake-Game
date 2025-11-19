#pragma once
#include <QWidget>
#include <QTimer>
#include <memory>
#include "IGameAPI.h"
#include "SnakeWidget.h"
#include <QVBoxLayout>

class GameScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameScreen(QWidget* parent = nullptr);

    void start();
    void keyPress(QKeyEvent* event);

signals:
    void gameFinished();
    void backToMenuRequested();

private slots:
    void gameOver();
    void restartGame();

private:
    std::unique_ptr<IGameAPI> gameApi;
    SnakeWidget* snakeWidget;
    QTimer* gameTimer;
};
