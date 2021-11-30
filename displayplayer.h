#ifndef DISPLAYPLAYER_H
#define DISPLAYPLAYER_H

#include <QTabWidget>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QIcon>
#include <QSize>
#include "player.h"

const QSize ButtonSize = QSize(30,30);

struct ShipIcon {
    QIcon battleship = QIcon(":/img/ShipIcons/battleship.png");
    QIcon carrier = QIcon(":/img/ShipIcons/carrier.png");
    QIcon cruiser = QIcon(":/img/ShipIcons/cruiser.png");
    QIcon destroyer = QIcon(":/img/ShipIcons/destroyer.png");
    QIcon submarine = QIcon(":/img/ShipIcons/submarine.png");
    QIcon hit = QIcon(":/img/ShipIcons/boom.png");
    QIcon fire = QIcon(":/img/ShipIcons/fire.png");
    QIcon none = QIcon(":/img/ShipIcons/blank.png");
};

class FiringTab : public QWidget
{
    Q_OBJECT
public:
    FiringTab(Player *p = nullptr, ComputerPlayer *opponent = nullptr);
    void BlockClick() {EnableClick = false;}
    void ActivateClick() {EnableClick = true;}
private:
    Player *p;
    ComputerPlayer *opponent;
    QVector<QPushButton *> buttonList;
    QLineEdit *announce;
    bool EnableClick;
    QTimer *timer;

    QPushButton* createButton(QIcon &icon, const char* member);
public slots:
    void ChangeOnClick();
    void ComputerTurn();
    void ChangeSquare(int index, bool isHit);
    void ReceiveMessage(QString message);
};

class ShipBoardTab : public QWidget
{
    Q_OBJECT
public:
    ShipBoardTab(Player *p = nullptr, ComputerPlayer *opponent = nullptr);
private:
    Player *p;
    ComputerPlayer *opponent;
    QVector<QPushButton *> buttonList;

public slots:
    void ChangeSquare(int index, bool isHit);
    void SetShip(int index, Ship ship);
};

class DisplayPlayer : public QTabWidget
{
    Q_OBJECT
public:
    DisplayPlayer(Player *p = nullptr, ComputerPlayer *opponent = nullptr);

private:
    Player *p;
    ComputerPlayer *opponent;
public slots:
    void WinAnnoucement();
    void LostAnnouncement();
};

#endif // DISPLAYPLAYER_H
