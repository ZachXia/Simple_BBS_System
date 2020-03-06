#ifndef BOARD_H
#define BOARD_H

#include "post.h"
#include <QVector>
#include <QString>
#include <QTextStream>

class board
{
public:
    board(unsigned int bid, QString n);

    QString getName();
    unsigned int getId();
    int getModeratorId();
    void setModerator(int uid);
    friend QTextStream &operator << (QTextStream &stream, board &b);
    friend QTextStream &operator >> (QTextStream &stream, board* &b);
private:

    unsigned int id;
    QString name;
    int moderatorId;  //无版主 = -1
};

#endif // BOARD_H
