#include "login.h"
#include <QApplication>
#include "controller.h"
#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/style/blue.css");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());
    file.close();

    login w;
    w.show();

    return a.exec();
}
