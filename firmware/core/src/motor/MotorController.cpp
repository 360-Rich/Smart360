#include "motor/MotorController.h"
#include "motor/RampGenerator.h"

namespace Smart360
{

void MotorController::initialize()
{
    state = MotorState{};
    profile = MotionProfile{};

    state.mode = MotorMode::Idle;
}

void MotorController::update(float deltaTime)
{
    if (deltaTime <= 0.0f)
    {
        return;
    }

    // Stop / deceleration phase
    if (!profile.valid)
    {
        if (state.velocity == 0.0f)
        {
            return;
        }

        const float previousVelocity = state.velocity;

        state.velocity = RampGenerator::calculateVelocity(
            state.velocity,
            0.0f,
            profile.maxAcceleration,
            profile.maxDeceleration,
            deltaTime);

        state.acceleration =
            (state.velocity - previousVelocity) / deltaTime;

        state.position += state.velocity * deltaTime;

        if (state.velocity == 0.0f)
        {
            state.acceleration = 0.0f;
            state.direction = MotorDirection::Stopped;
            state.mode = MotorMode::Idle;
        }

        return;
    }

    // Normal commanded motion
    if (!profile.validate())
    {
        return;
    }

    if (state.mode == MotorMode::Ready)
    {
        state.mode = MotorMode::Moving;
    }

    state.targetPosition = profile.targetPosition;

    const float targetVelocity =
        profile.maxVelocity *
        static_cast<float>(profile.direction);

    const float previousVelocity = state.velocity;

    state.velocity = RampGenerator::calculateVelocity(
        state.velocity,
        targetVelocity,
        profile.maxAcceleration,
        profile.maxDeceleration,
        deltaTime);

    state.acceleration =
        (state.velocity - previousVelocity) / deltaTime;

    const float nextPosition =
        state.position + (state.velocity * deltaTime);

    if (profile.direction == MotionDirection::Forward &&
        nextPosition >= profile.targetPosition)
    {
        state.position = profile.targetPosition;
        state.velocity = 0.0f;
        state.acceleration = 0.0f;
        state.direction = MotorDirection::Stopped;
        state.mode = MotorMode::Ready;
        return;
    }

    if (profile.direction == MotionDirection::Reverse &&
        nextPosition <= profile.targetPosition)
    {
        state.position = profile.targetPosition;
        state.velocity = 0.0f;
        state.acceleration = 0.0f;
        state.direction = MotorDirection::Stopped;
        state.mode = MotorMode::Ready;
        return;
    }

    state.position = nextPosition;

    if (state.velocity > 0.0f)
    {
        state.direction = MotorDirection::Forward;
    }
    else if (state.velocity < 0.0f)
    {
        state.direction = MotorDirection::Reverse;
    }
    else
    {
        state.direction = MotorDirection::Stopped;
    }
}

void MotorController::setTarget(const MotionProfile& newProfile)
{
    if (!newProfile.validate())
    {
        profile.valid = false;
        state.mode = MotorMode::Fault;
        return;
    }

    profile = newProfile;
    profile.valid = true;

    state.targetPosition = profile.targetPosition;
    state.maxVelocity = profile.maxVelocity;
    state.maxAcceleration = profile.maxAcceleration;
    state.acceleration = 0.0f;
    state.mode = MotorMode::Ready;
}

void MotorController::stop()
{
    profile.valid = false;

    if (state.velocity == 0.0f)
    {
        state.acceleration = 0.0f;
        state.direction = MotorDirection::Stopped;
        state.mode = MotorMode::Idle;
        return;
    }

    state.mode = MotorMode::Moving;
}

const MotorState& MotorController::getState() const
{
    return state;
}

} // namespace Smart360