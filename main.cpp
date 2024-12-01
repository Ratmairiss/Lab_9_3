
#include <QApplication>
#include "FigureCollection.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QFile file(":/new/prefix1/style.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());
    file.close();

    FigureCollection w;
    w.show();

    return a.exec();
}