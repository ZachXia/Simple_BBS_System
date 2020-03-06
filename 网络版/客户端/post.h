#ifndef POST_H
#define POST_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QTextStream>

class post
{
public:
    post(unsigned int nId, unsigned int nUserId, unsigned int nBoardId, QString nTitle, QString nContent);
    void setTitle(QString t);
    QString getTitle();
    void setContent(QString c);
    QString getContent();
    QDateTime getTime();
    unsigned int getId();
    unsigned int getUserId();
    unsigned int getBoardId();
    void setTime(QString t);


private:
    unsigned int id;
    unsigned int userId;
    unsigned int boardId;
    QString title;
    QString content;
    QDateTime time;

};


#endif // POST_H
