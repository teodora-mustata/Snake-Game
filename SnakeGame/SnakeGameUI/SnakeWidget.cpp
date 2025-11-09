
#include "SnakeWidget.h"
#include <QPainter>
#include <algorithm>

SnakeWidget::SnakeWidget(IGameAPI* api, QWidget* parent)
    : QWidget(parent), api(api)
{
    api->attachMapObserver(this);
    api->attachSnakeObserver(this);

    fruits = api->getFruits();
    snakeBody = api->getSnakeBody();
}

void SnakeWidget::update(MapEvent event, int x, int y) {
    if (event == MapEvent::FruitSpawned) {
        fruits.push_back({ x, y });
    }
    else if (event == MapEvent::FruitRemoved) {
        fruits.erase(std::remove(fruits.begin(), fruits.end(), std::make_pair(x, y)), fruits.end());
    }
    repaint();
}

void SnakeWidget::update(SnakeEvent event) {
    if (event == SnakeEvent::Move || event == SnakeEvent::AteFruit) {
        snakeBody = api->getSnakeBody();
        repaint();
    }
    else if (event == SnakeEvent::HitWall || event == SnakeEvent::HitSelf) {
        snakeAlive = false;
        repaint();
    }
}

void SnakeWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int rows = 20;
    int cols = 20;

    int cellW = width() / cols;
    int cellH = height() / rows;

    p.setPen(Qt::gray);
    for (int i = 0; i <= cols; ++i)
        p.drawLine(i * cellW, 0, i * cellW, height());
    for (int j = 0; j <= rows; ++j)
        p.drawLine(0, j * cellH, width(), j * cellH);

    p.setBrush(Qt::red);
    for (auto& fruit : fruits)
        p.drawEllipse(fruit.first * cellW, fruit.second * cellH, cellW, cellH);

    for (size_t i = 0; i < snakeBody.size(); ++i) {
        p.setBrush(i == 0 ? Qt::darkGreen : Qt::green);
        p.drawRect(snakeBody[i].first * cellW, snakeBody[i].second * cellH, cellW, cellH);
    }
}
