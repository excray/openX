#include "openx.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    openX w;
    w.show();

    return a.exec();
}
