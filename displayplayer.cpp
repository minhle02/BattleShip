#include "displayplayer.h"

#include <QApplication>
#include <QMessageBox>
#include <QTimer>

DisplayPlayer::DisplayPlayer(Player *p, ComputerPlayer *opponent) : p(p), opponent(opponent)
{
    this->addTab(new FiringTab(p, opponent), "Firing");
    this->addTab(new ShipBoardTab(p,opponent), "Ships");
    connect(p,SIGNAL(Win()),this,SLOT(WinAnnoucement()));
    connect(opponent,SIGNAL(Win()),this,SLOT(LostAnnouncement()));
}

void DisplayPlayer::WinAnnoucement()
{
    QMessageBox msgBox;
    msgBox.setText("Congratulation. You Win");
    msgBox.exec();
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),QApplication::instance(),SLOT(quit()));
    timer->start(000);
}

void DisplayPlayer::LostAnnouncement()
{
    QMessageBox msgBox;
    msgBox.setText("Sorry. You Lost");
    msgBox.exec();
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),QApplication::instance(),SLOT(quit()));
    timer->start(000);
}

FiringTab::FiringTab(Player *p, ComputerPlayer *opponent) : p(p), opponent(opponent)
{
    QGridLayout *mainlayout = new QGridLayout;
    EnableClick = true;

    QLineEdit *windowName = new QLineEdit;
    windowName->setReadOnly(true);
    windowName->setAlignment(Qt::AlignCenter);
    windowName->setText("Firing Board");

    QFont font = windowName->font();
    font.setPointSize(font.pointSize() + 10);
    windowName->setFont(font);
    mainlayout->addWidget(windowName,0,0,1,SIZE+1);

    QPushButton* colHeading[SIZE];
    for (int i = 0; i < SIZE; i++) {
        colHeading[i] = new QPushButton();
        char c = 'A' + i;
        colHeading[i]->setText((QString) c);
        colHeading[i]->resize(ButtonSize);
        colHeading[i]->setCheckable(false);
        mainlayout->addWidget(colHeading[i],1,i+1);
    }

    QPushButton* rowHeading[SIZE];
    for (int i = 0; i < SIZE; i++) {
        rowHeading[i] = new QPushButton();
        rowHeading[i]->setText(QString::number(i+1));
        rowHeading[i]->resize(ButtonSize);
        rowHeading[i]->setCheckable(false);
        mainlayout->addWidget(rowHeading[i],i+2,0);
    }

    ShipIcon s;
    for (int i = 0; i < SIZE*SIZE; i++) {
        QPushButton *button = createButton(s.none,SLOT(ChangeOnClick()));
        buttonList.push_back(button);
        mainlayout->addWidget(button, (i/10) + 2, (i%10) + 1);
    }

    announce = new QLineEdit;
    announce->setReadOnly(true);
    mainlayout->addWidget(announce,SIZE+3,0,1,SIZE+1);
    this->setLayout(mainlayout);
    QSize tabSize = this->size();
    this->setFixedSize(tabSize);

    connect(p,SIGNAL(SendCoordinate(int,bool)), this,SLOT(ChangeSquare(int,bool)) );
    connect(p,SIGNAL(SendMessage(QString)), this,SLOT(ReceiveMessage(QString)) );
}

QPushButton *FiringTab::createButton(QIcon &icon, const char *member)
{
    QPushButton *b = new QPushButton(this);
    b->setIcon(icon);
    connect(b,SIGNAL(clicked()),this,member);
    return b;
}

void FiringTab::ChangeOnClick()
{
    if (EnableClick)
    {
        this->BlockClick();
        QPushButton *clickButton = qobject_cast<QPushButton*>(sender());
        clickButton->setCheckable(false);
        int index = buttonList.indexOf(clickButton);
        if (index < 0 || index > SIZE*SIZE)
            throw std::runtime_error("Unkown index");

        p->FireAt(*opponent,index);
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()),this,SLOT(ComputerTurn()));
        timer->start(1000);
    }
}

void FiringTab::ComputerTurn()
{
    opponent->RandomFire(*p);
    delete timer;
    this->ActivateClick();
}

void FiringTab::ChangeSquare(int index, bool isHit)
{
    QPushButton *button = buttonList.at(index);
    ShipIcon s;
    QIcon icon = (isHit) ? s.hit : s.fire;
    button->setIcon(icon);
    button->setCheckable(false);
}

void FiringTab::ReceiveMessage(QString message)
{
    announce->setText(message);
}

ShipBoardTab::ShipBoardTab(Player *p, ComputerPlayer *opponent) : p(p), opponent(opponent)
{
    QGridLayout *mainlayout = new QGridLayout;

    QLineEdit *windowName = new QLineEdit;
    windowName->setReadOnly(true);
    windowName->setAlignment(Qt::AlignCenter);
    windowName->setText("Ship Board");

    QFont font = windowName->font();
    font.setPointSize(font.pointSize() + 10);
    windowName->setFont(font);
    mainlayout->addWidget(windowName,0,0,1,SIZE+1);

    QPushButton* colHeading[SIZE];
    for (int i = 0; i < SIZE; i++) {
        colHeading[i] = new QPushButton();
        char c = 'A' + i;
        colHeading[i]->setText((QString) c);
        colHeading[i]->resize(ButtonSize);
        colHeading[i]->setCheckable(false);
        mainlayout->addWidget(colHeading[i],1,i+1);
    }

    QPushButton* rowHeading[SIZE];
    for (int i = 0; i < SIZE; i++) {
        rowHeading[i] = new QPushButton();
        rowHeading[i]->setText(QString::number(i+1));
        rowHeading[i]->resize(ButtonSize);
        rowHeading[i]->setCheckable(false);
        mainlayout->addWidget(rowHeading[i],i+2,0);
    }

    ShipIcon s;
    for (int i = 0; i < SIZE*SIZE; i++) {
        QPushButton *button = new QPushButton(this);
        button->setIcon(s.none);
        buttonList.push_back(button);
        mainlayout->addWidget(button, (i/10) + 2, (i%10) + 1);
    }

    QLineEdit *line = new QLineEdit;
    line->setReadOnly(true);
    mainlayout->addWidget(line,SIZE+3,0,1,SIZE+1);
    QSize tabSize = this->size();
    this->setFixedSize(tabSize);

    this->setLayout(mainlayout);
    connect(opponent, SIGNAL(SendCoordinate(int, bool)), this, SLOT(ChangeSquare(int,bool)));
    connect(p, SIGNAL(SendShipPos(int, Ship)), this, SLOT(SetShip(int, Ship)));
}

void ShipBoardTab::ChangeSquare(int index, bool isHit)
{
    QPushButton *button = buttonList.at(index);
    ShipIcon s;
    QIcon icon = (isHit) ? s.hit : s.fire;
    button->setIcon(icon);
    button->setCheckable(false);
}

void ShipBoardTab::SetShip(int index, Ship ship)
{
    ShipIcon s;
    QIcon icon;
    if (ship == Carrier)
        icon = s.carrier;
    else if (ship == Cruiser)
        icon = s.cruiser;
    else if (ship == Battleship)
        icon = s.battleship;
    else if (ship == Destroyer)
        icon = s.destroyer;
    else if (ship == Submarine)
        icon = s.submarine;
    else
        icon = s.none;
    QPushButton *button = buttonList.at(index);
    button->setIcon(icon);
}
