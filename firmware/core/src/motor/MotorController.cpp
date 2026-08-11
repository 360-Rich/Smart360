#include "motor/MotorController.h"
#include "motor/RampGenerator.h"

namespace Smart360
{

void MotorController::initialize()
{
    state = MotorState{};
    profile = MotionProfile{};
}

void MotorController::update(float deltaTime)
{
    if (!profile.validate())
    {
        return;
    }

    state.velocity = RampGenerator::calculateVelocity(
        state.velocity,
        profile.maxVelocity *
            static_cast<float>(profile.direction),
        profile.maxAcceleration,
        profile.maxDeceleration,
        deltaTime);

    state.targetPosition = profile.targetPosition;

    state.position += state.velocity * deltaTime;

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
        return;
    }

    profile = newProfile;
    profile.valid = true;
}

void MotorController::stop()
{
    profile.valid = false;

    state.velocity = 0.0f;
    state.direction = MotorDirection::Stopped;
}

const MotorState& MotorController::getState() const
{
    return state;
}

} // namespace Smart360
