#ifndef PLAYGROUND_WIDGET_H
#define PLAYGROUND_WIDGET_H

#include "../game/include.h"
#include "characterCell.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

class PlaygroundWidget : public QWidget {
    Q_OBJECT

  private:
    QPushButton *backButton;
    QLabel *timerLabel;
    QLabel *coins;
    QTimer *timer;
    CharacterCell *cells[ROWS][COLUMNS];

  private slots:
    void updateTimerLabel(bool reset = false);
    void startTimer();

  public:
    PlaygroundWidget(QWidget *parent = 0);
};

#endif