#include "plotswindow.h"
#include "randomgenerator.h"

#include <iostream>
#include <cstdio>
#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char** argv) {
    //freopen ("trend.txt","w",stdout);
    RandomGenerator::randomize();
    QApplication app(argc, argv);
    PlotsWindow window;
    window.show();
    int exitcode = app.exec();
    RandomGenerator::destroy();
    return exitcode;
}
