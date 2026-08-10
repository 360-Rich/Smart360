#pragma once

#include <stdint.h>

namespace Smart360
{

enum class MotionDirection : int8_t
{
    Reverse = -1,
    Forward = 1
};

struct MotionProfile
{
    float targetPosition = 0.0f;

    float maxVelocity = 100.0f;
    float maxAcceleration = 100.0f;
    float maxDeceleration = 100.0f;

    MotionDirection direction = MotionDirection::Forward;

    bool valid = false;

    bool validate() const;
};

} // namespace Smart360
