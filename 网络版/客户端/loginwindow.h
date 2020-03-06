#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "mainwindow.h"


namespace Ui {
class loginWindow;
}

class loginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit loginWindow(QWidget *parent = 0);
    ~loginWindow();

private slots:
    void on_btn_login_clicked();

    void on_btn_netSetting_clicked();

private:
    Ui::loginWindow *ui;

    void updateBoardList();
    void updatePostList();
};

#endif // LOGINWINDOW_H
