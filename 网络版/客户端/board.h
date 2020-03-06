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
    QString getModeratorName();
    void setModeratorName(QString BM);
    void setModerator(int uid);

private:

    unsigned int id;
    QString name;
    QString moderatorName;
    int moderatorId;  //无版主 = -1
};

#endif // BOARD_H
