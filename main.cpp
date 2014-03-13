#include <QApplication>
#include "randomgenerator.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(doge);
    RandomGenerator::randomize();
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();
    int exitcode = app.exec();
    RandomGenerator::destroy();
    return exitcode;
}
