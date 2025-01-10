#include <QApplication>
#include "EQPasswordCreator.hpp"
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    if (translator.load(QLocale(), "", "", "resources", ".qm"))
    {
        a.installTranslator(&translator);
    }

    EQPasswordCreator w;
    w.show();
    return a.exec();
}