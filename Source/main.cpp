#include <QApplication>
#include "../Headers/EQPasswordCreator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EQPasswordCreator w;
    w.show();
    return a.exec();
}