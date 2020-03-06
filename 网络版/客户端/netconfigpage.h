#ifndef NETCONFIGPAGE_H
#define NETCONFIGPAGE_H

#include <QWidget>

namespace Ui {
class netConfigPage;
}

class netConfigPage : public QWidget
{
    Q_OBJECT

public:
    explicit netConfigPage(QWidget *parent = 0);
    ~netConfigPage();

private slots:
    void on_btn_apply_clicked();

private:
    Ui::netConfigPage *ui;
};

#endif // NETCONFIGPAGE_H
