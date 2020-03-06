#include "board.h"
#include "clientctrl.h"

board::board(unsigned int bid, QString n)
{
    this->id = bid;
    this->name = n;
    this->moderatorId = -1;
}

QString board::getName()
{
    return name;
}

unsigned int board::getId()
{
    return this->id;
}

int board::getModeratorId()
{
    return this->moderatorId;
}

void board::setModerator(int uid)
{
    this->moderatorId = uid;
}

QString board::getModeratorName()
{
    return moderatorName;
}

void board::setModeratorName(QString BM)
{
    moderatorName = BM;
}
