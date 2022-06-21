#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "include/error_graph.h"
#include "include/pid_table_model.h"
#include "include/simulator.h"
#include "ui_mainwindow.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    ErrorGraph* errorGraph;

private slots:
    void on_newSimulationButton_clicked();
    void on_nextSequenceButton_clicked();

signals:
    void startSimulation(const qreal targetCoordinate, const QVector<float>& pidCoefficients);
    void nextFrame();

private:
    PidTableModel* pidTableModel;
    Ui::MainWindow* ui;

    void initChart();
    void initTable();
};
#endif // MAINWINDOW_H
