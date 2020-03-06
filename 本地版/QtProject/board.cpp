#include "board.h"
#include "controller.h"

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

QTextStream &operator << (QTextStream &stream, board &b)
{
    stream << QString::number( b.getId() ) << ","
           << controller::encode( b.getName() ) << ","
           << QString::number( b.getModeratorId() ) << endl;
    return stream;
}

QTextStream &operator >> (QTextStream &stream, board* &b)
{
    QString str = stream.readLine();
    QStringList item = str.split(",");
    if(item.length() != 3)
    {
        b = nullptr;
        return stream;
    }
    QString tmp;
    tmp = item[0];
    unsigned int id = tmp.toInt();
    tmp = item[2];
    int mid = tmp.toInt();
    QString name = controller::decode( item[1] );

    b = new board(id, name);
    b->setModerator(mid);

}
