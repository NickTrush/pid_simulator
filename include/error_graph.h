#ifndef ERROR_GRAPH_H
#define ERROR_GRAPH_H

#include <QChart>
#include <QVector>
#include <QValueAxis>
#include <QLineSeries>
#include <QDebug>

class ErrorGraph: public QChart
{
    Q_OBJECT

public:
    explicit ErrorGraph(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    virtual ~ErrorGraph();

    void changeTargetCoordinate(const qreal newTargetCoordinate);

public slots:
    void setPoints(const QVector<QPointF>& points);

private:
    QPen currentPen;
    QPen targetPen;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QLineSeries* currentSeries;
    QLineSeries* targetSeries;
    qreal targetCoordinate;

    void initAxis();
    void initCurrentSeriesPen();
    void initTargetSeriesPen();
    void attachCurrentAxis();
    void removeCurrentSeries();
    void addCurrentSeries();
};

#endif // ERROR_GRAPH_H
