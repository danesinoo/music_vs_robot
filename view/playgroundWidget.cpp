#include "playgroundWidget.h"

#include "visitors/imageVisitor.h"

#include <QDebug>
#include <QGridLayout>
#include <QMessageBox>
#include <QVBoxLayout>

PlaygroundWidget::PlaygroundWidget(QWidget *parent)
    : QWidget(parent), backButton(new QPushButton("Back", this)), cash(new CashWidget(this)), timer(new TimerWidget(this)),
      violinButton(new InstrumentButton(new SlowDown(), "Violin ", this)),
      trumpetButton(new InstrumentButton(new ThreeRow(), "Trumpet ", this)),
      drumButton(new InstrumentButton(new ThreeColumn(), "Drum ", this)),
      saxophoneButton(new InstrumentButton(new DoubleLife(), "Sax ", this)),
      fluteButton(new InstrumentButton(new Sample(), "Flute ", this)), levelUpButton(new QPushButton("Level Up", this)),
      removeButton(new QPushButton("Remove", this)), hasFocus({-1, -1}) {

    /// Observers
    Game::getInstance()->PlaygroundPlayer::addObserver(this);
    Game::getInstance()->PlaygroundEnemy::addObserver(this);
    Game::getInstance()->PlaygroundDamage::addObserver(this);
    Game::getInstance()->ObservableGameInterface::addObserver(this);

    /// Navigation bar
    backButton->setFixedSize(100, 60);
    timer->setFixedSize(100, 50);
    cash->setFixedSize(100, 50);

    timer->setStyleSheet("background-color: #000000; color: #ffffff; "
                         "font-size: 20px; font-weight: bold;");
    cash->setStyleSheet("background-color: #000000; color: #ffffff; font-size: "
                        "20px; font-weight: bold;");

    QHBoxLayout *navBarLayout = new QHBoxLayout();

    navBarLayout->addWidget(backButton);
    navBarLayout->addWidget(timer);
    navBarLayout->addWidget(cash);

    navBarLayout->setAlignment(backButton, Qt::AlignLeft);
    navBarLayout->setAlignment(timer, Qt::AlignCenter);
    navBarLayout->setAlignment(cash, Qt::AlignRight);

    /// When the back button is clicked, the timer is stopped
    connect(backButton, SIGNAL(clicked()), parent, SLOT(endGame()));
    connect(this, SIGNAL(callEndGame()), parent, SLOT(endGame()));

    /// Side bar
    violinButton->setFixedSize(100, 50);
    trumpetButton->setFixedSize(100, 50);
    drumButton->setFixedSize(100, 50);
    saxophoneButton->setFixedSize(100, 50);
    fluteButton->setFixedSize(100, 50);

    levelUpButton->setFixedSize(100, 60);
    removeButton->setFixedSize(100, 60);

    QVBoxLayout *sideBarLayout = new QVBoxLayout();

    sideBarLayout->addWidget(violinButton);
    sideBarLayout->addWidget(trumpetButton);
    sideBarLayout->addWidget(drumButton);
    sideBarLayout->addWidget(saxophoneButton);
    sideBarLayout->addWidget(fluteButton);
    sideBarLayout->addWidget(levelUpButton);
    sideBarLayout->addWidget(removeButton);

    sideBarLayout->setAlignment(levelUpButton, Qt::AlignBottom);
    sideBarLayout->setAlignment(removeButton, Qt::AlignBottom);

    connect(levelUpButton, SIGNAL(clicked()), this, SLOT(levelUpEntity()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeEntity()));

    /// Grid
    QGridLayout *gridLayout = new QGridLayout();

    gridLayout->setHorizontalSpacing(1);
    gridLayout->setVerticalSpacing(1);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            cells[row][col] = new PlaygroundCellWidget(this);
            if (col == COLS - 1) {
                cells[row][col]->setStyleSheet("background-color: #3d3d3d; border: 1px solid "
                                               "black;");
            }

            gridLayout->addWidget(cells[row][col], row, col);

            connect(cells[row][col], &PlaygroundCellWidget::clicked, this, [this, row, col] {
                setFocus(row, col);
                insertEntity();
                showUpdatePrice();
            });
        }
    }

    QHBoxLayout *sidebar_gridLayout = new QHBoxLayout();

    sidebar_gridLayout->addLayout(sideBarLayout);
    sidebar_gridLayout->addLayout(gridLayout);

    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);

    vBoxLayout->addLayout(navBarLayout);
    vBoxLayout->addLayout(sidebar_gridLayout);

    setLayout(vBoxLayout);
}

void PlaygroundWidget::insertEntity() {
    PlayerAbstract *m = InstrumentButton::getSelectedInstrument();

    if (!m) {
        qDebug() << "No instrument selected!";
        return;
    }

    if (hasFocus.col == COLS - 1) {
        qDebug() << "Cannot insert entity in the last column!";
        return;
    }

    if (Game::getInstance()->insert(hasFocus.row, hasFocus.col, *m)) {
        qDebug() << "Player inserted entity!";
    } else {
        qDebug() << "Player cannot insert entity!";
        return;
    }

    InstrumentButton::removeSelectedInstrument();
}

void PlaygroundWidget::update(u32 r, u32 c, const PlayerAbstract *p) {
    updateCell(r, c);
    if (p) {
    }
}

void PlaygroundWidget::update(u32 r, u32 c, const EnemyWTool *e) {
    if (c == COLS)
        return;
    updateCell(r, c);
    if (e) {
    }
}

void PlaygroundWidget::update(u32 r, u32 c, const DamageAbstract *d) {
    updateCell(r, c);
    if (d) {
    }
}

void PlaygroundWidget::updateCell(u32 row, u32 col) {
    ImageVisitor iv;
    Game *g = Game::getInstance();
    if (col != COLS - 1 && !g->isEmpty(row, col)) {
        g->get(row, col).accept(&iv);
        cells[row][col]->setImage(iv.getPixmap());
        cells[row][col]->setLevel(g->get(row, col).getLevel());
        return;
    }

    if (!g->PlaygroundEnemy::isEmpty(row, col)) {
        g->PlaygroundEnemy::get(row, col)[0]->accept(&iv);
        cells[row][col]->setImage(iv.getPixmap());
        return;
    }

    if (!g->PlaygroundDamage::isEmpty(row, col)) {
        g->PlaygroundDamage::get(row, col).accept(&iv);
        cells[row][col]->setImage(iv.getPixmap());
        return;
    }

    cells[row][col]->setImage(new QPixmap());
    cells[row][col]->hideLevel();
}

void PlaygroundWidget::clearGame() {
    for (u32 row = 0; row < ROWS; row++) {
        for (u32 col = 0; col < COLS; col++) {
            cells[row][col]->setImage(new QPixmap());
            cells[row][col]->hideLevel();
        }
    }
}

void PlaygroundWidget::gameOver() {
    QMessageBox msgBox;
    msgBox.setText("Game over!");
    int buttonClicked = msgBox.exec();

    if (buttonClicked == QMessageBox::Ok) {
        emit callEndGame();
        std::cout << "Game over!" << std::endl;
    }
}

void PlaygroundWidget::levelUpEntity() {
    Game *g = Game::getInstance();
    if (getFocus() && !g->isEmpty(hasFocus.row, hasFocus.col)) {
        if (g->levelUp(hasFocus.row, hasFocus.col)) {
            qDebug() << "Player level up entity!";
        }
        showUpdatePrice();
    } else {
        qDebug() << "Player cannot level up entity!";
    }
}

void PlaygroundWidget::removeEntity() {
    Game *g = Game::getInstance();
    if (getFocus() && !g->isEmpty(hasFocus.row, hasFocus.col)) {
        g->remove(hasFocus.row, hasFocus.col);
        qDebug() << "Player remove entity!";
    } else {
        qDebug() << "Player cannot remove entity!";
    }
}

void PlaygroundWidget::setFocus(u32 row, u32 col) {
    hasFocus.row = row;
    hasFocus.col = col;
    //   qDebug() << "PlaygroundWidget::setFocus()";
}

void PlaygroundWidget::removeFocus() {
    hasFocus.row = -1;
    hasFocus.col = -1;
    //   qDebug() << "PlaygroundWidget::removeFocus()";
}

bool PlaygroundWidget::getFocus() const { return hasFocus.row != -1 && hasFocus.col != -1; }

void PlaygroundWidget::showUpdatePrice() {
    if (hasFocus.col == COLS - 1) {
        return;
    }
    const Game *g = Game::getInstance();
    if (!g->isEmpty(hasFocus.row, hasFocus.col)) {
        levelUpButton->setText("Level Up: " + QString::number(g->get(hasFocus.row, hasFocus.col).getCost()) + "$");
    } else {
        levelUpButton->setText("Level Up");
    }
}
