
#include <QApplication>
#include <iostream>
#include "mainui.h"

int main(int argc, char *argv[])
{
    QApplication a (argc, argv);
    qInfo() << "QtReadElf 工具.";
    MainUI mainUi;
    mainUi.show();
    return QApplication::exec ();
}
