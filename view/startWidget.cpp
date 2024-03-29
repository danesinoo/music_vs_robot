#include "startWidget.h"

#include "mainWindow.h"
#include <QApplication>
#include <QSpacerItem>
#include <QVBoxLayout>

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent), title(new QLabel("<font color='blue'>Music</font> "
                                        "<font color='green'>vs</font> "
                                        "<font color='red'>Robots</font>",
                                        this)),
      startButton(new QPushButton("New Game", this)), loadButton(new QPushButton("Load Game", this)),
      quitButton(new QPushButton("Quit", this)) {

    QSpacerItem *topSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem *bottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    title->setFixedSize(800, 170);
    startButton->setFixedSize(220, 50);
    loadButton->setFixedSize(220, 50);
    quitButton->setFixedSize(220, 50);

    title->setStyleSheet("font-size: 100px; font-weight: "
                         "bold; text-align: center;");
    title->setAlignment(Qt::AlignCenter);
    startButton->setStyleSheet("padding: 10px; color: black; font-size: 30px; background-color: #AAAAAA");
    loadButton->setStyleSheet("padding: 10px; color: black; font-size: 30px; background-color: #AAAAAA");
    quitButton->setStyleSheet("padding: 10px; color: red; font-size: 30px; background-color: #AAAAAA");

    /// Connect the buttons to the slots
    connect(startButton, SIGNAL(clicked()), parent, SLOT(newGame()));
    connect(loadButton, SIGNAL(clicked()), parent, SLOT(loadGame()));
    connect(quitButton, SIGNAL(clicked()), parent, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addItem(topSpacer);
    layout->addWidget(title);
    layout->addWidget(startButton);
    layout->addWidget(loadButton);
    layout->addWidget(quitButton);
    layout->addItem(bottomSpacer);

    layout->setAlignment(title, Qt::AlignCenter);
    layout->setAlignment(startButton, Qt::AlignCenter);
    layout->setAlignment(loadButton, Qt::AlignCenter);
    layout->setAlignment(quitButton, Qt::AlignCenter);

    setLayout(layout);
}