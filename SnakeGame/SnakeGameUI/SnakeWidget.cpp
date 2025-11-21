#include "SnakeWidget.h"
#include <QPainter>
#include <QTimer>
#include <algorithm>

SnakeWidget::SnakeWidget(IGameAPI* api, QWidget* parent)
    : QWidget(parent), api(api)
{
    api->attachMapObserver(this);
    api->attachSnakeObserver(this);

    fruits = api->getFruits();
    snakeBody = api->getSnakeBody();

    restartButton = new QPushButton("Restart Game", this);
    restartButton->setStyleSheet(
        "font-size: 20px; font-weight: bold; background-color: #28a745; color: white; border-radius: 8px; padding: 10px;");
    restartButton->setVisible(false);

    connect(restartButton, &QPushButton::clicked, [this]() {
        emit restartSignal();
        });

    backToMenuButton = new QPushButton("Back to Menu", this);
    backToMenuButton->setStyleSheet(
        "font-size: 20px; font-weight: bold; background-color: #007bff; color: white; border-radius: 8px; padding: 10px;");
    backToMenuButton->setVisible(false);

    connect(backToMenuButton, &QPushButton::clicked, [this]() {
        emit backToMenuSignal();
        });
}


void SnakeWidget::reset(IGameAPI* newApi) {
    api = newApi;
    fruits = api->getFruits();
    snakeBody = api->getSnakeBody();
    snakeAlive = true;

    api->attachMapObserver(this);
    api->attachSnakeObserver(this);

    restartButton->setVisible(false);
    backToMenuButton->setVisible(false);

    repaint();
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
        emit gameOverSignal();
        repaint();

        QTimer::singleShot(400, [this]() {
            int btnWidth = 180;
            int btnHeight = 50;

            restartButton->setGeometry(width() / 2 - btnWidth / 2, height() / 2 + 60, btnWidth, btnHeight);
            restartButton->show();

            backToMenuButton->setGeometry(width() / 2 - btnWidth / 2, height() / 2 + 120, btnWidth, btnHeight);
            backToMenuButton->show();
            });
    }
}

void SnakeWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QLinearGradient bgGradient(0, 0, width(), height());
    bgGradient.setColorAt(0, QColor(60, 60, 60));
    bgGradient.setColorAt(1, QColor(30, 30, 30));
    p.fillRect(rect(), bgGradient);

    int rows = 20;
    int cols = 20;
    int cellW = width() / cols;
    int cellH = height() / rows;

    QColor cellColor1(170, 215, 81);
    QColor cellColor2(162, 209, 73);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            p.setBrush((i + j) % 2 == 0 ? cellColor1 : cellColor2);
            p.setPen(Qt::NoPen);
            p.drawRect(j * cellW, i * cellH, cellW, cellH);
        }
    }

    for (auto& fruit : fruits) {
        QRadialGradient fruitGradient(fruit.first * cellW + cellW / 2, fruit.second * cellH + cellH / 2, cellW / 2);
        fruitGradient.setColorAt(0, Qt::yellow);
        fruitGradient.setColorAt(1, Qt::red);
        p.setBrush(fruitGradient);
        p.setPen(Qt::NoPen);
        p.drawEllipse(fruit.first * cellW + 2, fruit.second * cellH + 2, cellW - 4, cellH - 4);
    }

    for (size_t i = 0; i < snakeBody.size(); ++i) {
        QRect cellRect(snakeBody[i].first * cellW, snakeBody[i].second * cellH, cellW, cellH);

        QColor baseColor = (i == 0) ? QColor(0, 100, 0) : QColor(0, 150, 0);
        QColor altColor = (i == 0) ? QColor(0, 130, 0) : QColor(0, 180, 0); 

        int checkerSize = cellW / 2;
        for (int y = 0; y < 2; ++y) {
            for (int x = 0; x < 2; ++x) {
                QRect subRect(cellRect.x() + x * checkerSize, cellRect.y() + y * checkerSize, checkerSize, checkerSize);
                p.setBrush((x + y) % 2 == 0 ? baseColor : altColor);
                p.setPen(Qt::NoPen);
                p.drawRect(subRect);
            }
        }

        p.setPen(Qt::NoPen);
        QPainterPath path;
        path.addRoundedRect(cellRect, 5, 5);
        p.fillPath(path, p.brush());

        if (i == 0) {
            p.setBrush(Qt::white);
            int eyeSize = cellW / 5;
            p.drawEllipse(cellRect.x() + cellW / 4 - eyeSize / 2, cellRect.y() + cellH / 4 - eyeSize / 2, eyeSize, eyeSize);
            p.drawEllipse(cellRect.x() + 3 * cellW / 4 - eyeSize / 2, cellRect.y() + cellH / 4 - eyeSize / 2, eyeSize, eyeSize);
        }
    }

    if (!snakeAlive) {
        p.setBrush(QColor(0, 0, 0, 150));
        p.drawRect(rect());

        p.setPen(Qt::black);
        p.setFont(QFont("Arial", 28, QFont::Bold));
        p.drawText(rect().adjusted(2, 2, 2, 2), Qt::AlignCenter, "GAME OVER");

        p.setPen(Qt::red);
        p.drawText(rect(), Qt::AlignCenter, "GAME OVER");
    }

    QString scoreText = QString::number(api->getScore());
    p.setBrush(QColor(0, 0, 0, 150));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(10, 10, 80, 40, 10, 10);

    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 16, QFont::Bold));
    p.drawText(10, 10, 80, 40, Qt::AlignCenter, scoreText);

    int totalSeconds = static_cast<int>(api->getElapsedTime());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    QString timeText = QString("%1:%2")
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'));

    p.setBrush(QColor(0, 0, 0, 150));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(width() - 110, 10, 100, 40, 10, 10);

    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 16, QFont::Bold));
    p.drawText(width() - 110, 10, 100, 40, Qt::AlignCenter, timeText);

}