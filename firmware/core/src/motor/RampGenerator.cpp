#include "motor/RampGenerator.h"

namespace Smart360
{

float RampGenerator::calculateVelocity(
    float currentVelocity,
    float targetVelocity,
    float acceleration,
    float deceleration,
    float deltaTime)
{
    if (deltaTime <= 0.0f)
    {
        return currentVelocity;
    }

    if (currentVelocity < targetVelocity)
    {
        const float nextVelocity =
            currentVelocity + (acceleration * deltaTime);

        if (nextVelocity >= targetVelocity)
        {
            return targetVelocity;
        }

        return nextVelocity;
    }

    if (currentVelocity > targetVelocity)
    {
        const float nextVelocity =
            currentVelocity - (deceleration * deltaTime);

        if (nextVelocity <= targetVelocity)
        {
            return targetVelocity;
        }

        return nextVelocity;
    }

    return targetVelocity;
}

} // namespace Smart360
