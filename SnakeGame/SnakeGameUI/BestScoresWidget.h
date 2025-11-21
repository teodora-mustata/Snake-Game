#pragma once
#include <QWidget>

class BestScoresWidget : public QWidget {
    Q_OBJECT
public:
    explicit BestScoresWidget(QWidget* parent = nullptr);

    void refreshScores();
signals:
    void backToMenu();

protected:
    void paintEvent(QPaintEvent* event) override;
};
