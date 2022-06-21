#include "include/error_graph.h"

ErrorGraph::ErrorGraph(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    currentPen(Qt::darkGreen),
    targetPen(Qt::red),
    axisX(new QValueAxis),
    axisY(new QValueAxis),
    currentSeries(new QLineSeries(this)),
    targetSeries(new QLineSeries(this)),
    targetCoordinate(0)
{
    initAxis();
    initCurrentSeriesPen();
    initTargetSeriesPen();
    addCurrentSeries();
    attachCurrentAxis();
}

void ErrorGraph::initAxis()
{
    addAxis(axisX,Qt::AlignBottom);
    addAxis(axisY,Qt::AlignLeft);

    axisX->setTickCount(5);
    axisX->setRange(0, 20);
    axisX->setTitleText("Ось времени, с");
    axisY->setTickCount(5);
    axisY->setRange(0, 10);
    axisY->setTitleText("Ось координат, м");
}

void ErrorGraph::initCurrentSeriesPen()
{
    currentPen.setWidth(2);
    currentSeries->setPen(currentPen);
}

void ErrorGraph::initTargetSeriesPen()
{
    targetPen.setWidth(1);
    targetSeries->setPen(targetPen);
}

void ErrorGraph::attachCurrentAxis()
{
    for (auto axis: axes())
    {
        targetSeries->attachAxis(axis);
        currentSeries->attachAxis(axis);
    }
}

void ErrorGraph::removeCurrentSeries()
{
    removeSeries(targetSeries);
    removeSeries(currentSeries);
}

void ErrorGraph::addCurrentSeries()
{
    addSeries(targetSeries);
    addSeries(currentSeries);
}

ErrorGraph::~ErrorGraph()
{
    delete currentSeries;
    delete targetSeries;
}

void ErrorGraph::setPoints(const QVector<QPointF>& points)
{
    removeCurrentSeries();
    currentSeries->clear();
    targetSeries->clear();
    axisX->setRange(points.at(0).x(), points.at(points.size() - 1).x());
    targetSeries->append(axisX->min(), targetCoordinate);
    targetSeries->append(axisX->max(), targetCoordinate);
    currentSeries->append(points);
    addCurrentSeries();
    attachCurrentAxis();

/*    for (auto& point: points)
    {
        if (qAbs(point.y() - targetCoordinate) < 0.1) qDebug() << "Points near the target position 0.1m: " << point;
    } */
}

void ErrorGraph::changeTargetCoordinate(const qreal newTargetCoordinate)
{
    targetCoordinate = newTargetCoordinate;
}
