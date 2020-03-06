#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:

    void on_btn_login_clicked();

    void on_btn_close_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
