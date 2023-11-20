
#include <QApplication>
#include <iostream>
#include "testui.h"

int main(int argc, char *argv[])
{
    QApplication a (argc, argv);
    std::cout << "Hello, World!" << std::endl;
    TestUI testUi;
    testUi.show();
    return QApplication::exec ();
}
