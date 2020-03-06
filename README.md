# 使用说明
> 以下内容如未作特殊说明，均为第三版（网络版）的操作说明，对于第三版尚不支持的功能，会在说明中标注。

## 初始配置

C++学习论坛（高级版）的用户数据和帖子数据分别储存在`userdata`和`postdata`文件中，且已在压缩包中给出，需放在程序根目录使用。程序第一次运行且没有发现数据文件时会视为建立全新的论坛系统，程序会默认给定管理员账号和密码，用户可以通过管理员账户登陆后添加用户、添加版块完成论坛的初始化。也可以使用给定的数据覆盖程序自动生成的原文件实现数据的恢复。

C++学习论坛（网络版）分为`服务端`和`客户端`两部分，其中`客户端`无需配置，可以直接双击运行，并支持多用户登陆；`服务端`需要在根目录放入存有用户数据和帖子数据的`userdata`和`postdata`，正确保存后即可双击运行启动。

需要注意的是，网络版系统暂时不支持管理员功能，因此初始化的空论坛无法直接使用（无法管理用户、版块），请先导入两个数据文件后再进行使用。

## 功能说明
### 客户端功能

#### 登陆界面
![login](https://s2.ax1x.com/2020/03/06/3L0ort.jpg)
* 用户通过输入管理员分配的账号即可登陆系统，系统会根据用户的名字自动识别用户的身份，进入到不同的主界面模式。系统初始给定了如下几个用户：

| 身份|用户名|密码|
|:--:|:----:|:---:|
|管理员|admin|123|
|管理员|admin2|1234|
|普通用户|aaa|aaa|
|普通用户|sss|sss|
|普通用户|ddd|ddd|
|匿名用户|anonym|123|

* 在登陆界面的右上角，可以设置自定义服务器。程序默认连接`localhost`本地服务器。

#### 系统主界面
![mianwindow](https://s2.ax1x.com/2020/03/06/3L0IKI.jpg)

* 点击用户头像以查看个人信息（仅第二版支持）
* 点击刷新按钮以更新版块和帖子列表的显示
* 点击 `logout` 按钮注销当前用户
* 点击 `UserManager` 进入管理模式（仅限管理员用户，仅第二版支持）
* 点击 `new Post` 发表帖子（仅限普通用户）
* 点击板块列表选择版块，点击帖子列表显示帖子内容

#### 管理界面（仅第二版支持）
![manager](https://s2.ax1x.com/2020/03/06/3L0TqP.jpg)
管理界面仅限管理员操作，分为三个页面
* `Add User` 页面下新增用户，可以指定用户的身份
* `Set BM` 页面下任命版主，系统规定每个版块最多只有一名版主，同一用户可以担任不同版块版主
* `Add Board` 页面下新增板块

#### 其他功能（仅第二版支持）

* 普通用户可在查看帖子页面下进行评论
* 普通用户可以在查看帖子页面下删除自己发布的、无评论的帖子
* 版主可以在查看帖子页面下删除自己管理版块内的帖子

## 服务端功能
![server](https://s2.ax1x.com/2020/03/06/3L0f8H.jpg)

* 服务器端运行后自动从本地载入数据，无需手动操作。log窗口显示实时请求处理。点击右上角关闭按钮自动保存文件

# 程序结构
![prog](https://s2.ax1x.com/2020/03/06/3L0h2d.png)
*（注：仅代表逻辑组织方式，并非与实际调用关系一一对应）*

在第二版程序中有一个`controller`类负责存储数据、处理用户操作。在第三版中，`controller`被拆分为一个`ClientCtrl`类和一个`ServerCtrl`类，分别用来处理客户端和服务端的数据和操作。
## 客户端

客户端有几种基本的类代表论坛系统中的对象，分别为`post`、`board`、`comment`、`user`，还有Qt designer界面类`LoginWindow`、`MainWindow`、`PostPage`、`ViewPage`、`NetConfigPage`。

`ClientCtrl`是一个单例，仅在程序启动时构造一个实体，用来存储系统内的临时信息、处理用户的操作以及与服务端进行网络通信。

## 服务端

服务端没有复杂的用户操作，因此不需要各种界面类，`ServerWindow`既负责显示服务器运行信息，又承担了与客户端数据通信的任务。`ServerCtrl`是服务端存储数据、处理数据的对象，仅在启动时构造一次。

# 设计说明

## 设计思路

在客户端和服务端，除了给定的用户类、帖子类等类型，我还希望有一个类来专门存储数据、处理数据，而不是用界面类去实现用户操作的功能。因此我在两边都设定了controller类。

为了保证每个运行的程序中的数据都是唯一的，就必须要求程序中的controller对象唯一，因此我定义了静态函数`getInstance()`来返回自己的指针，保证每次调用时都能找啊唯一的对象。
```cpp
clientCtrl* clientCtrl::getInstance()
{
    if(ctrlPtr == nullptr)
        ctrlPtr = new clientCtrl;
    return ctrlPtr;
}
```

有了controller后，就可以在界面获取到用户操作后，调用controller中设计的函数，再用controller处理内存中的数据，以此做到界面与程序功能的独立性。

网络通信方面，为了更好的支持多用户操作，采用了短连接的方式，即每次客户端发出请求都要先与服务器建立连接再发送消息，得到服务器的正确响应后立即释放连接。

这样做的好处是节约了资源，方便多用户的实现，但缺陷在于无法收到服务端的更新消息，只能在客户端手动刷新显示。但考虑到论坛系统并不像实时通信系统一样对实时性有严格的需求，结合实际情况我选择了短连接方式。

## 数据结构与接口

帖子
```cpp
//post.h:

class post
{
public:
    post(unsigned int nId, unsigned int nUserId, 
         unsigned int nBoardId, QString nTitle, QString nContent);
    void setTitle(QString t);
    QString getTitle();
    void setContent(QString c);
    QString getContent();
    QDateTime getTime();
    unsigned int getId();
    unsigned int getUserId();
    unsigned int getBoardId();
    void setTime(QString t);

    QVector<comment*> commentList;  //评论列表

    friend QTextStream &operator << (QTextStream &stream, post &p);
    friend QTextStream &operator >> (QTextStream &stream, post* &p);
private:
    unsigned int id;           //帖子id
    unsigned int userId;       //发帖用户id
    unsigned int boardId;      //所属版块id
    QString title;             //帖子标题
    QString content;           //帖子内容
    QDateTime time;            //发帖时间

};
```
版块
```cpp
//board.h:

class board
{
public:
    board(unsigned int bid, QString n);

    QString getName();
    unsigned int getId();
    int getModeratorId();
    void setModerator(int uid);
    friend QTextStream &operator << (QTextStream &stream, board &b);
    friend QTextStream &operator >> (QTextStream &stream, board* &b);
private:

    unsigned int id;  //版块id
    QString name;     //板块名
    int moderatorId;  //版主id，无版主 = -1
};
```

评论
```cpp
//comment.h:

class comment
{
public:
    comment(unsigned int nUserId, QString nContent);
    unsigned int getUserId();
    QString getContent();
    QDateTime getTime();
    void setTime(QString s);

private:
    unsigned int userId;  //评论用户id
    QString content;      //评论内容
    QDateTime time;       //评论时间
};
```

用户
```cpp
//user.h：

class user
{
public:
    user();
    QString getName();
    QString getPswd();
    QString profile();
    unsigned int getId();
    int getStatus();
    int login(QString nm, QString pw);  //登陆
    void logout();                      //注销
    virtual int deletePost(unsigned int bid, 
                           unsigned int pid) = 0;  //删帖
    unsigned int getBoards();
    void setBoards(unsigned int bds);
    unsigned int boards;  //管理的板块数
    unsigned int id;   //用户id
    QString name;      //用户名
    QString pswd;      //密码
    int status;  //用户身份 admin = 0, BM = 1, user = 2, anonym = 3

    friend QTextStream &operator >> (QTextStream &stream, user* &u);
    friend QTextStream &operator << (QTextStream &stream, user &u);
};


//管理员

class admin : public user
{
public:
    admin(unsigned int uid, QString nm, QString pw);
    virtual int deletePost(unsigned int bid, unsigned int pid);
};

//普通用户

class normalUser : public user
{
public:
    normalUser();
    normalUser(unsigned int uid, QString nm, QString pw);
    virtual int deletePost(unsigned int bid, unsigned int pid);
};

//版主

class BMUser : public normalUser
{
public:
    BMUser(unsigned int uid, QString nm, QString pw);
    virtual int deletePost(unsigned int bid, unsigned int pid);
};

//匿名用户

class anonymUser : public normalUser
{
public:
    anonymUser(unsigned int uid, QString nm, QString pw);
};
```

服务端controller
```cpp
//serverCtrl.h

class serverCtrl
{
public:
    static serverCtrl* getInstance();   //返回自己的指针
    static QString encode(QString str);
    static QString decode(QString str);

    user* userLogin(QString nm, QString pw);
    void addNewPost(int uid, int bid, QString title, QString content);
    void addNewUser(int status, QString name, QString pswd);
    user* getUser(unsigned int uid);
    post* getPost(unsigned int pid);


    void load();    //从文件载入数据
    void save();    //保存数据到文件

    QVector<board*> boardList;  //板块列表
    QVector<post*> postList;    //帖子列表
    QVector<user*> userList;    //用户列表


private:
    serverCtrl();
    static serverCtrl *ctrlPtr;  //指向自己的指针

    unsigned int nextUserId;     //下一个分配的用户id
    unsigned int nextBoardId;    //下一个分配的版块id
    unsigned int nextPostId;     //下一个分配的帖子id
};
```

客户端controller
```cpp
//clientCtrl.h

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
    int mode;   // -1=未登录 0=管理员 1=版主 2=普通用户 3=匿名用户
    QString curUserName;  //当前登陆用户名
};
```

## 文件格式
用户数据和帖子数据均采用`ASCII`码方式存储，字符串均使用`Base64`编码。其中：

用户数据每行为一个单位，格式为
> 用户id,用户名,密码,身份,管理版块数

帖子数据每行为一个单位，版块格式为
> 版块id,版块名,版主id

直至读到分界符号`***`，帖子格式为
> 帖子id,发帖人id,所属版块id,发帖时间,标题,正文,评论数

评论格式为
> 评论人id,时间,内容

直至读到分界符号`***`

通过重载`>>`和`<<`操作符来读取各类型数据。

## 通信格式
客户端与服务器的通信过程中，以字符数组作为通信的数据结构，由于已经设计了文件的存储格式，所以在文件格式的基础上稍作改动形成了客户端与服务端的通信格式。

通信采用*请求-应答*方式，其中请求格式为
> 操作类型,用户id,其他选项

应答格式则同存储格式一致，返回所请求的信息。

# 系统测试

* 用户登陆与注销

![testlogin](https://s2.ax1x.com/2020/03/06/3L0HVf.png)

用户可以通过自己的账号密码登陆和注销，服务器能够正确响应。多用户可以同时登陆系统。

* 查看版块与帖子

![testread](https://s2.ax1x.com/2020/03/06/3L0qIS.png)

用户可以点击版块与帖子进行查看操作，多用户可以同时查看帖子。

* 发表帖子

![testpost](https://s2.ax1x.com/2020/03/06/3L0ba8.png)

用户可以发表新帖子，多用户状态下可在手动刷新后看到实时帖子信息。

* 系统管理、删帖等其他功能已在前两版中做过演示，不再赘述。

