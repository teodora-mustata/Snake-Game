#include "BestScoresWidget.h"
#include "ScoreManager.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QStyleOption>

BestScoresWidget::BestScoresWidget(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Best Scores");
    refreshScores();
}
void clearLayout(QWidget* widget)
{
    if (!widget) return;

    QList<QObject*> children = widget->children();
    for (QObject* obj : children) {
        QWidget* w = qobject_cast<QWidget*>(obj);
        if (w) {
            w->setParent(nullptr);
            w->deleteLater();
        }
    }

    if (widget->layout()) {
        QLayout* layout = widget->layout();
        widget->setLayout(nullptr);
        delete layout;
    }
}

void BestScoresWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter p(this);

    QLinearGradient bg(0, 0, width(), height());
    bg.setColorAt(0, QColor(40, 80, 40));   
    bg.setColorAt(1, QColor(70, 140, 70)); 

    p.fillRect(rect(), bg);

    QStyleOption opt;
    opt.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void BestScoresWidget::refreshScores()
{

    clearLayout(this);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Top 5 Scores");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size: 32px;"
        "font-weight: bold;"
        "color: white;"
        "margin: 20px;"
    );
    layout->addWidget(title);

    auto scores = ScoreManager::loadScores();

    if (scores.empty()) {
        QLabel* noScores = new QLabel("No scores yet.");
        noScores->setStyleSheet("font-size: 20px; color: white;");
        noScores->setAlignment(Qt::AlignCenter);
        layout->addWidget(noScores);
    }
    else {
        for (auto& entry : scores) {
            int score = entry.first;
            double time = entry.second;

            int minutes = static_cast<int>(time) / 60;
            int seconds = static_cast<int>(time) % 60;

            QString line = QString("Score: %1    Time: %2:%3")
                .arg(score)
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'));

            QLabel* lbl = new QLabel(line);
            lbl->setStyleSheet(
                "font-size: 22px;"
                "color: white;"
                "background-color: rgba(0,0,0,70);"
                "border-radius: 10px;"
                "padding: 8px 15px;"
            );
            lbl->setAlignment(Qt::AlignCenter);

            layout->addWidget(lbl);
        }
    }

    layout->addStretch();

    QPushButton* backBtn = new QPushButton("Back to Menu");
    backBtn->setStyleSheet(
        "font-size: 20px;"
        "font-weight: bold;"
        "background-color: #2e8b57;"      
        "color: white;"
        "border-radius: 10px;"
        "padding: 10px 20px;"
    );
    backBtn->setFixedWidth(200);

    layout->addWidget(backBtn, 0, Qt::AlignCenter);

    connect(backBtn, &QPushButton::clicked, this, &BestScoresWidget::backToMenu);
}
