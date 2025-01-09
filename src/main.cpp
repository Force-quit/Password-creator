#include <QApplication>
#include "EQPasswordCreator.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EQPasswordCreator w;
    w.show();
    return a.exec();
}