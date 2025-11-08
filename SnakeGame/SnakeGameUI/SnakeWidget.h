#pragma once
#include <QWidget>
#include <QTimer>
#include "GameController.h"

class SnakeWidget : public QWidget {
    Q_OBJECT
private:
    Map& map;
    Snake& snake;
    GameController& gameController;
    QTimer* timer;

public:
    SnakeWidget(Map& m, Snake& s, GameController& gc, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void onGameTick();
};
