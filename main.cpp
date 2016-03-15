#include "mainwindow.h"
#include <QApplication>

/*
 * TO DO:
 * Done 1. Reset data when mode changes.
 * Done 2. Add multipliers to axis.
 * 3. Set x axis to time.
 * 4. Add display controls.
 * 5. Add resize capabilities.
 * Done 6. Show data as lines.
*/

/*15-03-2016: v.1.0: Working version.
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
