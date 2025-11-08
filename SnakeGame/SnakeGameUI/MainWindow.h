#pragma once
#include <QMainWindow>
#include "SnakeWidget.h"
#include "Map.h"
#include "Snake.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
};
