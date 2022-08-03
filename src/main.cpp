#include "include/mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QThread>
#include <locale.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"rus");

    QApplication a(argc, argv);
    MainWindow w;
    Simulator simulator(1, 3, true, true, 10, 0);
    QThread simulatorThread;

    simulator.moveToThread(&simulatorThread);

    QObject::connect(&w, &MainWindow::startSimulation,
                     &simulator, &Simulator::startSimulation);

    QObject::connect(&w, &MainWindow::nextFrame,
                     &simulator, &Simulator::nextFrame);

    QObject::connect(&simulator, &Simulator::newPoints,
                     w.errorGraph, &ErrorGraph::setPoints);

    simulatorThread.start();

    w.show();
    QApplication::exec();

    simulatorThread.quit();
    simulatorThread.wait();

    return 0;

}
