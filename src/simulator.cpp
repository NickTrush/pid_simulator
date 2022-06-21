#include "include/simulator.h"
#include <QPointF>

template<typename Type>
Type minMax(Type min, Type max, Type value)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

Simulator::Simulator(qreal massOfObject,
                     qreal startingPosition,
                     bool isGravity,
                     bool isOppositeForce,
                     qreal noiseOfAccelerationPercent,
                     qreal randomConstantAccelerationPercent):
    QObject(nullptr),

    startingPosition(startingPosition),
    randomConstantAccelerationPercent(randomConstantAccelerationPercent),
    mass(massOfObject),
    coordinate(startingPosition),
    isGravity(isGravity),
    isOppositeForce(isOppositeForce),
    noiseOfAcceleration(noiseOfAccelerationPercent/100.0),

    targetCoordinate(0),
    force(0),
    acceleration(0),
    velocity(0),
    currentTime(0),
    pid(PID())
{
}

void Simulator::startSimulation(const qreal newTargetCoordinate, const QVector<float>& pidCoefficients)
{
    reset();
    pid.setPidCoefficients(pidCoefficients);
    targetCoordinate = newTargetCoordinate;

    qDebug() << "Start simulation!";
    nextFrame();
    points.clear();
}

void Simulator::nextFrame()
{
    qDebug() << "Next frame!";
    auto newFrameEnd = currentTime + frameSizeInSeconds;
    while(currentTime < newFrameEnd) mainLoop();
    emit newPoints(points);
    points.clear();
}

void Simulator::mainLoop()
{
    calculateForce();
    calculateAcceleration();
    calculateCoordinate();
    calculateVelocity();
//    qDebug() << "In main loop! coordinate:" << coordinate << "currentTime:" << currentTime;
    currentTime += deltaTime;
    points.push_back(QPointF(currentTime, coordinate));
}

qreal Simulator::getNoiseAcceleration()
{
    return (QRandomGenerator::global()->generateDouble() - 0.5) * 2 * noiseOfAcceleration;
}

void Simulator::calculateForce()
{
//    qDebug() << "Coordinate: " << coordinate << "Target coordinate: " << targetCoordinate;
    force = minMax<qreal>(-static_cast<int>(isOppositeForce) * maxForce, maxForce, pid.calculateEffect(coordinate, targetCoordinate));
//    qDebug() << "Time: " << currentTime << "Force: " << force;
}

void Simulator::calculateAcceleration()
{
    acceleration = force/mass + accelerationOfGravity*(-static_cast<int>(isGravity) + randomConstantAcceleration + getNoiseAcceleration());
//    qDebug() << "Acceleration: " << acceleration;
}

void Simulator::calculateVelocity()
{
    velocity += acceleration * deltaTime;
//    qDebug() << "Velocity: " << velocity;
}

void Simulator::calculateCoordinate()
{

    auto deltaX = velocity * deltaTime + (acceleration * deltaTime * deltaTime)/2;
    coordinate += deltaX;
    coordinate = minMax<qreal>(0, maxHeight, coordinate);
//    qDebug() << "Result coordinate: " << coordinate;
}

void Simulator::reset()
{
    randomConstantAcceleration = (QRandomGenerator::global()->generateDouble() - 0.5) * 2 * randomConstantAccelerationPercent/100.0;
    coordinate = startingPosition;
    currentTime = force = acceleration = velocity = 0;
    pid.reset();
    points.clear();
}
