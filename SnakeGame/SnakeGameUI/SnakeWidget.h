#pragma once
#include <QWidget>
#include <vector>
#include "IObserverMap.h"
#include "IObserverSnake.h"
#include "IGameAPI.h"
#include <QPushButton>
#include <QPainterPath>

class SnakeWidget : public QWidget, public IObserverMap, public IObserverSnake {
    Q_OBJECT

private:
    IGameAPI* api;
    std::vector<std::pair<int, int>> fruits;
    std::vector<std::pair<int, int>> snakeBody;
    bool snakeAlive = true;
    QPushButton* restartButton = nullptr;
    QPushButton* backToMenuButton = nullptr;

public:
    SnakeWidget(IGameAPI* api, QWidget* parent = nullptr);
    void reset(IGameAPI* newApi);

    void update(MapEvent event, int x, int y) override;
    void update(SnakeEvent event) override;

protected:
    void paintEvent(QPaintEvent* event) override;
signals:
    void gameOverSignal();
    void restartSignal();
    void backToMenuSignal();
};
