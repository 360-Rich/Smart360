#pragma once

#include <stdint.h>

namespace Smart360
{

enum class MotorMode : uint8_t
{
    Idle = 0,
    Homing,
    Ready,
    Moving,
    Paused,
    Fault
};

enum class MotorDirection : int8_t
{
    Reverse = -1,
    Stopped = 0,
    Forward = 1
};

struct MotorState
{
    MotorMode mode = MotorMode::Idle;
    MotorDirection direction = MotorDirection::Stopped;

    float position = 0.0f;
    float targetPosition = 0.0f;

    float velocity = 0.0f;
    float acceleration = 0.0f;

    float maxVelocity = 100.0f;
    float maxAcceleration = 100.0f;

    bool enabled = false;
};

} // namespace Smart360
