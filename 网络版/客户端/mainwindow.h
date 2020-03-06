#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class mainWindow;
}

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

private slots:
    void on_btn_logout_clicked();

    void on_btn_f5_clicked();

    void on_ls_board_clicked(const QModelIndex &index);

    void on_ls_post_clicked(const QModelIndex &index);

    void on_btn_new_clicked();

    void on_btn_usrManager_clicked();

    void on_btn_netSetting_clicked();

private:
    Ui::mainWindow *ui;
    void init();
    void updateBoardList();
    void updatePostList();
};

#endif // MAINWINDOW_H
