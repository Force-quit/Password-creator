#include "EQPasswordCreator.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

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