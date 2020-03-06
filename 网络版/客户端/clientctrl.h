#ifndef CLIENTCTRL_H
#define CLIENTCTRL_H


#include <QObject>
#include <QTcpSocket>
#include "board.h"
#include "post.h"

class clientCtrl : public QObject
{
    Q_OBJECT
public:
    explicit clientCtrl(QObject *parent = nullptr);
    static clientCtrl* getInstance();  //返回自己的指针

    void setHost(QString ip, qint16 port);
    int userLogin(QString nm, QString pw);
    int getCurUserId();
    int getCurBoardId();
    int getCurpostId();
    void setCurBoardId(int bid);
    void setCurPostId(int bid);
    int getMode();
    QString getCurUserName();
    int newPost(QString title, QString content);
    void getPostList();
    QStringList getPost(int pid);

    QVector<board*> boardList;   //板块列表
    QVector<post*> postList;     //帖子列表

private:
    static clientCtrl* ctrlPtr;  //指向自己的指针
    QTcpSocket *tcpSocket;

    static QString encode(QString str);
    static QString decode(QString str);

    void connectToHost();
    void disconnectFromHost();
    void dataClear();

    QString curHostIP;  //当前ip
    qint16 curHostPort; //当前端口
    int curUserId;      //当前用户id
    int curBoardId;     //当前版块id
    int curPostId;      //当前帖子id
    int mode;   //当前用户登陆模式 -1=未登录 0=管理员 1=版主 2=普通用户 3=匿名用户
    QString curUserName;  //当前登陆用户名
};

#endif // CLIENTCTRL_H
