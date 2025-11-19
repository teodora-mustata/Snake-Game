#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MenuWidget : public QWidget {
    Q_OBJECT
public:
    QPushButton* playButton;
    QPushButton* scoresButton;
    QPushButton* exitButton;

    MenuWidget(QWidget* parent = nullptr);
};
