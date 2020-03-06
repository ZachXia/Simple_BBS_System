#include "post.h"
#include "controller.h"

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

QTextStream &operator << (QTextStream &stream, post &p)
{
    stream << QString::number( p.getId() ) << ","
           << QString::number( p.getUserId() ) << ","
           << QString::number( p.getBoardId() ) << ","
           << controller::encode( p.getTime().toString() ) << ","
           << controller::encode( p.getTitle() ) << ","
           << controller::encode( p.getContent() ) << ","
           << p.commentList.length() << endl;
    for(QVector<comment*>::iterator iter = p.commentList.begin(); iter != p.commentList.end(); iter++)
    {
        stream << (*iter)->getUserId() << ","
               << controller::encode( (*iter)->getTime().toString() ) << ","
               << controller::encode( (*iter)->getContent() ) << endl;
    }
    return stream;
}

QTextStream &operator >> (QTextStream &stream, post* &p)
{
    QString str = stream.readLine();
    QStringList item = str.split(",");
    if(item.length() != 7)
    {
        p = nullptr;
        return stream;
    }
    QString tmp;
    tmp = item[0];
    unsigned int pid = tmp.toInt();
    tmp = item[1];
    unsigned int uid = tmp.toInt();
    tmp = item[2];
    unsigned int bid = tmp.toInt();
    QString time = controller::decode( item[3] );
    QString title = controller::decode( item[4] );
    QString content = controller::decode( item[5] );
    p = new post(pid, uid, bid, title, content);
    p->setTime(time);

    tmp = item[6];
    unsigned int cNum = tmp.toInt();
    //读评论
    while (cNum--) {
        str = stream.readLine();
        item = str.split(",");
        if(item.length() != 3)
            return stream;
        tmp = item[0];
        uid = tmp.toInt();
        time = controller::decode( item[1] );
        content = controller::decode( item[2] );
        comment *c = new comment(uid, content);
        c->setTime(time);
        p->commentList.push_back(c);
    }

    return stream;
}
