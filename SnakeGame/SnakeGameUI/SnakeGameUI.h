#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SnakeGameUI.h"

class SnakeGameUI : public QMainWindow
{
    Q_OBJECT

public:
    SnakeGameUI(QWidget *parent = nullptr);
    ~SnakeGameUI();

private:
    Ui::SnakeGameUIClass ui;
};

