#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QRandomGenerator>
#include <QTimer>
#include "include/pid.h"
#include <QDebug>
#include <QVector>

class Simulator : public QObject
{
    Q_OBJECT

public:
    Simulator(qreal massOfObject,
              qreal startingPosition,
              bool isThereGravity = true,
              bool isOppositeForce = false,
              qreal accelerationNoise = 0,
              qreal randomConstantAcceleration = 0);

public slots:
    void startSimulation(const qreal newTargetCoordinate, const QVector<float>& pidCoefficients);
    void nextFrame();

signals:
    void newPoints(const QVector<QPointF>& points);

private:
    const qreal startingPosition;
    const qreal frameSizeInSeconds = 20;
    const qreal accelerationOfGravity = 9.81;
    const qreal deltaTime = 0.01;
    const qreal maxHeight = 100;
    const qreal maxForce = 20;

    const qreal randomConstantAccelerationPercent;

    qreal mass;
    qreal coordinate;
    bool isGravity;
    bool isOppositeForce;
    qreal noiseOfAcceleration;
    qreal randomConstantAcceleration;

    qreal targetCoordinate;

    qreal force;
    qreal acceleration;
    qreal velocity;


    qreal currentTime;
    PID pid;
    QVector<QPointF> points;

    void mainLoop();
    qreal getNoiseAcceleration();
    void calculateForce();
    void calculateAcceleration();
    void calculateVelocity();
    void calculateCoordinate();
    void reset();
};

#endif // SIMULATOR_H
