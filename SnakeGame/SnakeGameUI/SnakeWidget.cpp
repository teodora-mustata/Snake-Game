#include "SnakeWidget.h"
#include <QPainter>
#include <QKeyEvent>

SnakeWidget::SnakeWidget(Map& m, Snake& s, GameController& gc, QWidget* parent)
    : QWidget(parent), map(m), snake(s), gameController(gc)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SnakeWidget::onGameTick);
    timer->start(200);
}

void SnakeWidget::onGameTick() {
    gameController.update(0.2);
    update();
}

void SnakeWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int rows = map.getHeight();
    int cols = map.getWidth();

    int cellWidth = width() / cols;
    int cellHeight = height() / rows;

    painter.setPen(Qt::black);
    for (int i = 0; i <= cols; ++i) {
        painter.drawLine(i * cellWidth, 0, i * cellWidth, height());
    }
    for (int j = 0; j <= rows; ++j) {
        painter.drawLine(0, j * cellHeight, width(), j * cellHeight);
    }

    painter.setBrush(Qt::red); 
    for (const auto& fruit : map.getFruits()) {
        int x = fruit.first * cellWidth;
        int y = fruit.second * cellHeight;

        QPoint triangle[3] = {
            QPoint(x + cellWidth / 2, y),
            QPoint(x, y + cellHeight),
            QPoint(x + cellWidth, y + cellHeight)
        };
        painter.drawPolygon(triangle, 3);
    }

    const auto& body = snake.getBody();
    for (size_t i = 0; i < body.size(); ++i) {
        int x = body[i].first * cellWidth;
        int y = body[i].second * cellHeight;

        if (i == 0) {
            painter.setBrush(Qt::green);
            painter.drawEllipse(x, y, cellWidth, cellHeight);
        }
        else {
            painter.setBrush(Qt::darkGreen);
            painter.drawRect(x, y, cellWidth, cellHeight);
        }
    }
}


void SnakeWidget::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W: snake.setDirection(Direction::Up); break;
    case Qt::Key_S: snake.setDirection(Direction::Down); break;
    case Qt::Key_A: snake.setDirection(Direction::Left); break;
    case Qt::Key_D: snake.setDirection(Direction::Right); break;
    }
}
