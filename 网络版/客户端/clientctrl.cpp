#include "clientctrl.h"
#include <QHostAddress>

clientCtrl::clientCtrl(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket;
    curUserId = -1;
    curHostIP = "127.0.0.1";
    curHostPort = 6666;
}

clientCtrl* clientCtrl::ctrlPtr = new clientCtrl;

clientCtrl* clientCtrl::getInstance()
{
    if(ctrlPtr == nullptr)
    {
        ctrlPtr = new clientCtrl;
    }
    return ctrlPtr;
}

void clientCtrl::connectToHost()
{
    tcpSocket->connectToHost(QHostAddress(curHostIP), curHostPort);
}

void clientCtrl::disconnectFromHost()
{
    tcpSocket->disconnectFromHost();
}

QString clientCtrl::encode(QString str)
{
    QByteArray a;
    a.append(str);
    return a.toBase64();
}

QString clientCtrl::decode(QString str)
{
    QByteArray a;
    a.append(str);
    return QByteArray::fromBase64(a);
}

//0用户登录，返回登陆成功的用户id，或-1=登陆失败，-2=网络错误
int clientCtrl::userLogin(QString nm, QString pw)
{
    connectToHost();

    //发送
    QString str = "0,-1," + encode(nm) + "," + encode(pw) + "\n";
    QByteArray p;
    p.append(str);
    tcpSocket->write(p);

    //接受
    if( tcpSocket->waitForReadyRead(1000) == false){
        disconnectFromHost();
        return -2;
    }
    QString rcv = tcpSocket->readLine();
    QStringList item = rcv.split(",");

    this->curUserId = item[0].toInt();
    this->mode = item[1].toInt();
    this->curUserName = decode( item[2] );

    disconnectFromHost();
    return curUserId;
}

//1 请求帖子列表
void clientCtrl::getPostList()
{
    connectToHost();

    //发送
    QString str = "1," + QString::number(curUserId) + "\n";
    QByteArray p;
    p.append(str);
    tcpSocket->write(p);

    //接受
    if( tcpSocket->waitForReadyRead(1000) == false){
        throw -2;
    }

    dataClear();
    do{
        //读入板块
        QString rcv = tcpSocket->readLine();

        QStringList item = rcv.split(",");
        if(item.size() != 3){
            break;
        }
        int bid = item[0].toInt();
        QString BM = decode( item[1] );
        QString nm = decode( item[2] );
        board* bPtr = new board(bid, nm);
        bPtr->setModeratorName(BM);
        boardList.push_back(bPtr);
    }while(1);
    do{
        //读入帖子（标题）
        QString rcv = tcpSocket->readLine();
        QStringList item = rcv.split(",");
        if(item.size() != 3){
            break;
        }
        int id = item[0].toInt();
        int bid = item[1].toInt();
        QString tt = decode(item[2]);
        post* pPtr = new post(id, 0, bid, tt, "");
        postList.push_back(pPtr);
    }while(1);

    disconnectFromHost();
}

//2 请求完整帖子用于显示
QStringList clientCtrl::getPost(int pid)
{
    connectToHost();

    //发送
    QString str = "2," + QString::number(curUserId) + "," + QString::number(pid) + "\n";
    QByteArray p;
    p.append(str);
    tcpSocket->write(p);

    //接受
    if( tcpSocket->waitForReadyRead(1000) == false){
        throw -2;
    }
    QStringList pStrings;
    QString rcv = tcpSocket->readLine();
    QStringList item = rcv.split(",");
    if(item.size() != 5){
        disconnectFromHost();
        return pStrings;
    }
    QString userName = decode( item[0] );
    QString time = decode( item[1] );
    QString title = decode( item[2] );
    QString content = decode( item[3] );
    int commentNum = item[4].toInt();
    pStrings.push_back(userName);
    pStrings.push_back(time);
    pStrings.push_back(title);
    pStrings.push_back(content);
    pStrings.push_back(item[4]);
    while(commentNum--){
        QString rcv = tcpSocket->readLine();
        QStringList item = rcv.split(",");
        if(item.size() != 3){
            break;
        }
        QString cName = decode(item[0]);
        QString cTime = decode(item[1]);
        QString cContent = decode(item[2]);
        pStrings.push_back(cName);
        pStrings.push_back(cTime);
        pStrings.push_back(cContent);
    }

    disconnectFromHost();
    return pStrings;
}

//3 请求发帖
int clientCtrl::newPost(QString title, QString content)
{
    connectToHost();

    QString str = "3," + QString::number(curUserId) + "," + QString::number(curBoardId) + "," + encode(title) + "," + encode(content) + "\n";
    QByteArray a;
    a.append(str);
    tcpSocket->write(a);

    if( tcpSocket->waitForReadyRead(1000) == false){
        return -2;
    }
    QString rcv = tcpSocket->readLine();
    disconnectFromHost();
    return rcv.toInt();
}

void clientCtrl::dataClear()
{
    for(QVector<board*>::iterator iter = boardList.begin(); iter != boardList.end(); iter++)
    {
        delete (*iter);
    }
    for(QVector<post*>::iterator iter = postList.begin(); iter != postList.end(); iter++)
    {
        delete (*iter);
    }
    boardList.clear();
    postList.clear();
}

void clientCtrl::setHost(QString ip, qint16 port)
{
    curHostIP = ip;
    curHostPort = port;
}

void clientCtrl::setCurBoardId(int bid)
{
    curBoardId = bid;
}

void clientCtrl::setCurPostId(int pid)
{
    curPostId = pid;
}

int clientCtrl::getCurBoardId()
{
    return curBoardId;
}

int clientCtrl::getCurpostId()
{
    return curPostId;
}

int clientCtrl::getCurUserId()
{
    return curUserId;
}

int clientCtrl::getMode()
{
    return mode;
}

QString clientCtrl::getCurUserName()
{
    return curUserName;
}
