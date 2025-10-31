#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GameInterface.h"

class GameInterface : public QMainWindow
{
    Q_OBJECT

public:
    GameInterface(QWidget *parent = nullptr);
    ~GameInterface();

private:
    Ui::GameInterfaceClass ui;
};

