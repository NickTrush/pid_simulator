#include "include/mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    errorGraph(new ErrorGraph()),
    pidTableModel(new PidTableModel),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initChart();
    initTable();

    ui->newSimulationButton->setText("Новая симуляция");
    ui->newSimulationButton->setStyleSheet("color:green");
}

MainWindow::~MainWindow()
{
    delete pidTableModel;
    delete errorGraph;
    delete ui;
}

void MainWindow::initChart(void)
{
    errorGraph->setTitle("Зависимость ошибки от времени");
    errorGraph->legend()->hide();
    errorGraph->setAnimationOptions(QChart::SeriesAnimations);
    //errorGraph->layout().setContentsMargins(0, 0, 0, 0);
    errorGraph->setBackgroundRoundness(0);
    ui->errorGraphView->setChart(errorGraph);
}

void MainWindow::initTable(void)
{
    ui->indicatorsTableView->setModel(pidTableModel);
    ui->indicatorsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->indicatorsTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_newSimulationButton_clicked()
{
    errorGraph->changeTargetCoordinate(pidTableModel->getTargetCoordinate());
    emit startSimulation(pidTableModel->getTargetCoordinate(),
                         pidTableModel->getPidCoefficients());
}

void MainWindow::on_nextSequenceButton_clicked()
{
    emit nextFrame();
}
