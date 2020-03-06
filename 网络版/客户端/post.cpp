#include "post.h"
#include "clientctrl.h"

post::post(unsigned int nId, unsigned int nUserId,unsigned int nBoardId, QString nTitle, QString nContent)
{
    this->id = nId;
    this->userId = nUserId;
    this->boardId = nBoardId;
    this->title = nTitle;
    this->content = nContent;
    this->time = time.currentDateTime();
}

void post::setContent(QString c)
{
    content = c;
}

void post::setTitle(QString t)
{
    title = t;
}

QString post::getTitle()
{
    return title;
}

QString post::getContent()
{
    return content;
}

QDateTime post::getTime()
{
    return time;
}

unsigned int post::getId()
{
    return id;
}

unsigned int post::getBoardId()
{
    return boardId;
}

unsigned int post::getUserId()
{
    return userId;
}

void post::setTime(QString t)
{
    this->time = QDateTime::fromString(t);
}
