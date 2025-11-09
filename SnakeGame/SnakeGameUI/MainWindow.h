


#pragma once
#include <QMainWindow>
#include <QTimer>
#include "IGameAPI.h"
#include "SnakeWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    IGameAPI* gameApi;        
    SnakeWidget* snakeWidget;
    QTimer* gameTimer;

protected:
    void keyPressEvent(QKeyEvent* event) override;

public:
    explicit MainWindow(IGameAPI* api, QWidget* parent = nullptr);
};
