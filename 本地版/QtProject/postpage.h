#ifndef POSTPAGE_H
#define POSTPAGE_H

#include <QDialog>

namespace Ui {
class postPage;
}

class postPage : public QDialog
{
    Q_OBJECT

public:
    explicit postPage(QWidget *parent = nullptr);
    ~postPage();

private slots:
    void on_btn_cancel_clicked();
    void on_btn_post_clicked();

private:
    Ui::postPage *ui;
};

#endif // POSTPAGE_H
