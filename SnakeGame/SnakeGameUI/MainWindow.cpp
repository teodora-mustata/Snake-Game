#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    menu = new MenuWidget();
    game = new GameScreen();
    scores = new BestScoresWidget();

    stack->addWidget(menu);
    stack->addWidget(game);
    stack->addWidget(scores);

    connect(menu->playButton, &QPushButton::clicked, [this]() {
        stack->setCurrentIndex(1);
        game->start();
        });

    connect(menu->scoresButton, &QPushButton::clicked, [this]() {
        scores->refreshScores();
        stack->setCurrentIndex(2);
        });

    connect(menu->exitButton, &QPushButton::clicked, this, &MainWindow::close);

    connect(game, &GameScreen::backToMenuRequested, [this]() {
        game->restartGame();
        stack->setCurrentIndex(0);
        });

    connect(scores, &BestScoresWidget::backToMenu, [this]() {
        stack->setCurrentIndex(0); 
        });

    setFixedSize(500, 500);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (stack->currentWidget() == game) {
        game->keyPress(event);
    }
}
