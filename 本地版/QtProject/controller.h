#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QVector>
#include "board.h"
#include "user.h"

class controller
{
public:

    static controller* getInstance();

    void init();
    void addNewPost(QString title, QString content);
    void addNewComment(QString content);
    void addNewBoard(QString name);
    void addNewUser(int status, QString name, QString pswd);
    void setBoardModerator(unsigned int bid, int uid);

    unsigned int getCurUserId();
    unsigned int getCurBoardId();
    unsigned int getCurPostId();
    void setCurUserId(unsigned int i);
    void setCurBoardId(unsigned int i);
    void setCurPostId(unsigned int i);
    user* userLogin(QString nm, QString pw);

    user* getUser(unsigned int uid);
    post* getPost(unsigned int pid);
    board* getBoard(unsigned int bid);

    QVector<board*> boardList;
    QVector<user*> userList;
    QVector<post*> postList;

    static QString encode(QString str);
    static QString decode(QString str);

    int save();
    void load();
    bool firstRun;

private:
    controller();

    static controller* ctrlptr;

    unsigned int curBoardId;
    unsigned int curPostId;
    unsigned int curUserId;

    unsigned int nextBoardId;
    unsigned int nextPostId;
    unsigned int nextUserId;



};

#endif // CONTROLLER_H
