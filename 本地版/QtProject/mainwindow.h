#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QVector>
#include "post.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addNewPost(post* ptr);

private slots:
    void on_btn_new_clicked();


    void on_ls_post_clicked(const QModelIndex &index);
    void on_ls_board_clicked(const QModelIndex &index);

    void on_btn_headPhoto_clicked();

    void on_btn_logout_clicked();

    void on_btn_usrManager_clicked();

    void on_btn_close_clicked();

private:
    Ui::MainWindow *ui;
    void updatePostList();
    void updateBoardList();
    void init();
};

#endif // MAINWINDOW_H
