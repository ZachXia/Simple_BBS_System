#ifndef COMMENT_H
#define COMMENT_H

#include <QString>
#include <QDateTime>

class comment
{
public:
    comment(unsigned int nUserId, QString nContent);
    unsigned int getUserId();
    QString getContent();
    QDateTime getTime();
    void setTime(QString s);

private:
    unsigned int userId;
    QString content;
    QDateTime time;

    //time;
};

#endif // COMMENT_H


