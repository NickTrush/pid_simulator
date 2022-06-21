#include "include/pid.h"
#include <QDebug>
int16_t PID::calculateEffect(float currentValue, float targetValue)
{
    error = targetValue - currentValue;
    p = kP * error;
    i += kI * error;
    d = kD * (error - prevError);
    prevError = error;
    return static_cast<int16_t>(p + i + d);
}
