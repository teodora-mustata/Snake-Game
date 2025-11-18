


#pragma once
#include <QMainWindow>
#include <QTimer>
#include "IGameAPI.h"
#include "SnakeWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    //IGameAPI* gameApi; 
    std::unique_ptr<IGameAPI> gameApi;
    SnakeWidget* snakeWidget;
    QTimer* gameTimer;

protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void startGame();
    void gameOver();

public:
    /*explicit MainWindow(IGameAPI* api, QWidget* parent = nullptr);*/
    explicit MainWindow(std::unique_ptr<IGameAPI> api, QWidget* parent = nullptr);

};
