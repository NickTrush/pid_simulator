#pragma once

#include <QVector>
#include <QTextStream>
#include <QString>

class PID
{

public:
    explicit PID() = default;
    qint16 calculateEffect(float currentValue, float targetValue);

    inline QVector<float> getComponents() const
        {return QVector<float>({p, i, d});}

    inline QVector<float> getCoefficients() const
        {return QVector<float>({kP, kI, kD});}

    inline float getPCoefficient() const
        {return kP;}

    inline float getICoefficient() const
        {return kI;}

    inline float getDCoefficient() const
        {return kD;}

    inline void setPCoefficient(float newP)
        {kP = newP;}

    inline void setICoefficient(float newI)
        {kI = newI;}

    inline void setDCoefficient(float newD)
        {kD = newD;}

    inline void reset()
        {i = prevError = 0;}

    inline void setIComponent(const float iComponent)
        {i = iComponent;}

    inline float getIComponent() const
        {return i;}

    inline void setPrevError(float newPrevError)
        {prevError = newPrevError;}

    inline friend QTextStream& operator >> (QTextStream& out, PID& pid)
        {return out >> pid.kP >> pid.kI >> pid.kD;}

    inline friend QTextStream& operator << (QTextStream& in, const PID& pid)
        {return in << pid.kP << " " << pid.kI << " " << pid.kD;}

    inline operator QString() const
        {return "MyPID {" + QString::number(static_cast<double>(kP)) + ", " + QString::number(static_cast<double>(kI)) + ", " + QString::number(static_cast<double>(kD)) +"}";}

    template<typename Container>
    void setPidCoefficients(const Container& pidCoefficients);

private:
    float p = 0, i = 0, d = 0;
    float kP = 0, kI = 0, kD = 0;
    float error = 0, prevError = 0;
};

template<typename Container>
void PID::setPidCoefficients(const Container& pidCoefficients)
{
    kP = pidCoefficients.at(0);
    kI = pidCoefficients.at(1);
    kD = pidCoefficients.at(2);
}
