#include "MenuWidget.h"
#include <QVBoxLayout>
#include <QLabel>

MenuWidget::MenuWidget(QWidget* parent)
    : QWidget(parent)
{
    QLabel* background = new QLabel(this);
    background->setPixmap(QPixmap(":/SnakeGameUI/snake_wallpaper.jpg").scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    background->setScaledContents(true);
    background->setGeometry(0, 0, 800, 600); 
    background->lower();

    QString buttonStyle = R"(
        QPushButton {
            background-color: rgba(0,0,0,150);
            color: white;
            border-radius: 15px;
            font-size: 22px;
            padding: 10px 20px;
            font-family: 'Segoe UI';
            border: 2px solid rgba(255,255,255,80);
        }
        QPushButton:hover {
            background-color: rgba(255,255,255,180);
            color: black;
        }
    )";

    QLabel* title = new QLabel("Snake Game");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size: 48px;"
        "font-weight: bold;"
        "color: white;"
        "font-family: 'Segoe UI';"
        "text-shadow: 3px 3px 6px black;"
    );

    playButton = new QPushButton("Play");
    scoresButton = new QPushButton("Best Scores");
    exitButton = new QPushButton("Exit");

    playButton->setStyleSheet(buttonStyle);
    scoresButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout* box = new QVBoxLayout();
    box->setAlignment(Qt::AlignCenter);
    box->setSpacing(25);

    box->addWidget(title);
    box->addWidget(playButton, 0, Qt::AlignCenter);
    box->addWidget(scoresButton, 0, Qt::AlignCenter);
    box->addWidget(exitButton, 0, Qt::AlignCenter);

    mainLayout->addLayout(box);
}
