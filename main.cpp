#include "gatisconsole.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GatisConsole w;
//    w.show();
    return a.exec();
}
