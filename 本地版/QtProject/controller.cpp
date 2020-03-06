#include "controller.h"
#include <QFile>
#include <QByteArray>

#include <QDebug>

controller::controller()
{

    firstRun = true;
    //this->init();
}

controller* controller::ctrlptr = new controller;

controller* controller::getInstance()
{
    if(!ctrlptr)
    {
        ctrlptr = new controller;
    }
    return ctrlptr;
}

void controller::init()
{
    nextBoardId = 0;
    nextPostId = 0;
    nextUserId = 0;

    addNewUser(0, "admin", "123");
    addNewUser(0, "admin2", "1234");
    addNewUser(3, "anonym", "123");
    addNewUser(2, "aaa", "aaa");
    addNewUser(2, "sss", "sss");
    addNewUser(2, "ddd", "ddd");

    addNewBoard("C++ 教程");
    addNewPost("C++ 简介","C++ 是一种静态类型的、编译式的、通用的、大小写敏感的、不规则的编程语言，"
                        "支持过程化编程、面向对象编程和""泛型编程。C++ 被认为是一种中级语言，它综合"
                        "了高级语言和低级语言的特点。C++ 是由 Bjarne Stroustrup 于 1979 年在新泽"
                        "西州美利山贝尔实验室开始设计开发的。C++ 进一步扩充和完善了 C 语言，最初命名"
                        "为带类的C，后来在 1983 年更名为 C++。 C++ 是 C 的一个超集，事实上，任何合法"
                        "的 C 程序都是合法的 C++ 程序。注意：使用静态类型的编程语言是在编译时执行类型"
                        "检查，而不是在运行时执行类型检查。");
    addNewPost("C++ 数据类型","使用编程语言进行编程时，需要用到各种变量来存储各种信息。变量保留的是它所"
                          "存储的值的内存位置。这意味着，当您创建一个变量时，就会在内存中保留一些空间。"
                          "您可能需要存储各种数据类型（比如字符型、宽字符型、整型、浮点型、双浮点型、布尔"
                          "型等）的信息，操作系统会根据变量的数据类型，来分配内存和决定在保留内存中存储什"
                          "么。");

    addNewBoard("C++ 面向对象");
    addNewPost("C++ 类 & 对象","C++ 在 C 语言的基础上增加了面向对象编程，C++ 支持面向对象程序设计。类是 "
                            "C++ 的核心特性，通常被称为用户定义的类型。类用于指定对象的形式，它包含了数据"
                            "表示法和用于处理数据的方法。类中的数据和方法称为类的成员。函数在一个类中被称为"
                            "类的成员。");
    addNewPost("C++ 继承","面向对象程序设计中最重要的一个概念是继承。继承允许我们依据另一个类来定义一个类，"
                        "这使得创建和维护一个应用程序变得更容易。这样做，也达到了重用代码功能和提高执行时间"
                        "的效果。");
    addNewComment("希望大家多多练习");
    addNewComment("谢谢大家");
}

void controller::addNewUser(int status, QString name, QString pswd)
{
    user* ptr;
    switch (status)
    {
        case 0:
            ptr = new admin(nextUserId, name, pswd);
            break;
        case 1:
            ptr = new BMUser(nextUserId, name, pswd);
            break;
        case 2:
            ptr = new normalUser(nextUserId, name, pswd);
            break;
        case 3:
            ptr = new anonymUser(nextUserId, name, pswd);
        default:
            break;
    }

    this->userList.append(ptr);
    curUserId = nextUserId;
    nextUserId++;
}

void controller::addNewPost(QString title, QString content)
{
    post* ptr = new post(nextPostId, curUserId, curBoardId, title, content);
    this->postList.append(ptr);
    curPostId = nextPostId;
    nextPostId++;
}

void controller::addNewComment(QString content)
{
    comment* ptr = new comment(curUserId, content);
    getPost(curPostId)->commentList.append(ptr);
}

void controller::addNewBoard(QString name)
{
    board* ptr = new board(nextBoardId, name);
    this->boardList.append(ptr);
    curBoardId = nextBoardId;
    nextBoardId++;
}

void controller::setBoardModerator(unsigned int bid, int uid)
{
    board* b = getBoard(bid);

    if( b->getModeratorId() != -1 )
    {//撤下原版主
        int boards = getUser( b->getModeratorId() )->getBoards();

        if(boards > 1)
            getUser( b->getModeratorId() )->setBoards(boards - 1);
        else
        {//原版主降为普通用户
            for(QVector<user*>::iterator iter = userList.begin(); iter != userList.end(); iter++)
            {
                if( (*iter)->getId() != b->getModeratorId() )
                    continue;
                user* tmp = *iter;
                *iter = new normalUser(tmp->getId(), tmp->getName(), tmp->getPswd());
                delete tmp;
                break;
            }
        }
    }

    //添加新版主
    if(uid >= 0)
    {
        int boards = getUser(uid)->getBoards();
        if(boards > 0)
        {//用户已经是版主
            getUser(uid)->setBoards(boards + 1);
        }
        else
        {//提升普通用户为版主
            for(QVector<user*>::iterator iter = userList.begin(); iter != userList.end(); iter++)
            {
                if( (*iter)->getId() != uid )
                    continue;
                user* tmp = *iter;
                *iter = new BMUser(tmp->getId(), tmp->getName(), tmp->getPswd());
                delete tmp;
                break;
            }

        }
    }

    getBoard(bid)->setModerator(uid);
}

user* controller::userLogin(QString nm, QString pw)
{
    for(QVector<user*>::iterator iter = userList.begin(); iter != userList.end(); iter++)
    {
        if((*iter)->login(nm, pw) == 1)
        {
            this->curUserId = (*iter)->getId();
            return (*iter);
        }

    }
    return nullptr;
}

unsigned int controller::getCurUserId()
{
    return curUserId;
}

user* controller::getUser(unsigned int uid)
{
    for(QVector<user*>::iterator iter = userList.begin(); iter != userList.end(); iter++)
    {
        if(uid == (*iter)->id)
        {
            return (*iter);
        }
    }
    return nullptr;
}

post* controller::getPost(unsigned int pid)
{
    for(QVector<post*>::iterator iter = postList.begin(); iter != postList.end(); iter++)
    {
        if(pid == (*iter)->getId())
        {
            return (*iter);
        }
    }
    return nullptr;
}

board* controller::getBoard(unsigned int bid)
{
    for(QVector<board*>::iterator iter = boardList.begin(); iter != boardList.end(); iter++)
    {
        if(bid == (*iter)->getId())
        {
            return (*iter);
        }
    }
    return nullptr;
}

unsigned int controller::getCurBoardId()
{
    return curBoardId;
}

unsigned int controller::getCurPostId()
{
    return curPostId;
}

void controller::setCurBoardId(unsigned int i)
{
    curBoardId = i;
}

void controller::setCurPostId(unsigned int i)
{
    curPostId = i;
}

void controller::setCurUserId(unsigned int i)
{
    curUserId = i;
}

QString controller::encode(QString str)
{
    QByteArray a;
    a.append(str);
    return a.toBase64();
}

QString controller::decode(QString str)
{
    QByteArray a;
    a.append(str);
    return QByteArray::fromBase64(a);
}

int controller::save()
{
    //写用户信息
    QFile fu("userdata");
    fu.open(QFile::WriteOnly);
    QTextStream outU(&fu);
    for(QVector<user*>::iterator iter = userList.begin(); iter != userList.end(); iter++)
    {
        outU << *(*iter);
    }
    fu.close();

    //写帖子信息
    QFile fp("postdata");
    fp.open(QFile::WriteOnly);
    QTextStream outP(&fp);
    for(QVector<board*>::iterator iter = boardList.begin(); iter != boardList.end(); iter++)
    {//board
        outP << *(*iter);
    }
    outP << "***" << endl;
    for(QVector<post*>::iterator iter = postList.begin(); iter != postList.end(); iter++)
    {//post
        outP << *(*iter);
    }
    outP << "***" << endl;
    outP << nextUserId << " "
         << nextBoardId << " "
         << nextPostId << endl;


    fp.close();
}

void controller::load()
{
    //读用户
    QFile fu("userdata");
    if( !fu.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        throw -1;
    }


    QTextStream inU(&fu);

    while(1){
        user* u;
        inU >> u;
        if(u == nullptr)
            break;
        userList.push_back(u);
    }

    fu.close();


    //读帖子
    QFile fp("postdata");
    if( !fp.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        throw -2;
    }


    QTextStream inP(&fp);

    while(1){
        //board
        board* b;
        inP >> b;
        if(b == nullptr)
            break;
        boardList.push_back(b);
    }
    while(1){
        //post
        post* p;
        inP >> p;
        if(p == nullptr)
            break;
        postList.push_back(p);
    }
    inP >> nextUserId >> nextBoardId >> nextPostId;


    fp.close();

}
