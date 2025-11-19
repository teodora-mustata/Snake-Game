#pragma once
#include <QMainWindow>
#include <QStackedWidget>

#include "MenuWidget.h"
#include "GameScreen.h"
#include "BestScoresWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    QStackedWidget* stack;
    MenuWidget* menu;
    GameScreen* game;
    BestScoresWidget* scores;
};
