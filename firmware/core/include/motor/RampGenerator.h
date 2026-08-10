#pragma once

namespace Smart360
{

class RampGenerator
{
public:
    static float calculateVelocity(
        float currentVelocity,
        float targetVelocity,
        float acceleration,
        float deceleration,
        float deltaTime);
};

} // namespace Smart360
