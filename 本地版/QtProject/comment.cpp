#include "comment.h"

comment::comment(unsigned int nUserId, QString nContent)
{
    this->userId = nUserId;
    this->content =nContent;
    this->time = time.currentDateTime();
}

unsigned int comment::getUserId()
{
    return this->userId;
}

QString comment::getContent()
{
    return this->content;
}

QDateTime comment::getTime()
{
    return this->time;
}

void comment::setTime(QString s)
{
    this->time = QDateTime::fromString(s);
}
