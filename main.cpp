#include "mainwindow.h"
#include <QApplication>

/*
 * TODO:
 * 1. Reset data when mode changes.
 * 2. Add multipliers to axis.
 * 3. Set x axis to time.
 * 4. Add display controls.
 * 5. Add resize capabilities.
 * 6. Show data as lines.
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
